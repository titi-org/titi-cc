#define _POSIX_C_SOURCE 200809L
#include "cc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct BufferState {
  char *mem_buffer_ptr;
  size_t mem_buffer_size;
  FILE *buffer_stream;
  struct BufferState *prev;
} BufferState;

static BufferState *buffer_stack = NULL;

void start_buffering(void) {
  if (mode != MODE_C_TO_RUN)
    return;

  /* Always push a new buffer state */
  BufferState *new_state = malloc(sizeof(BufferState));
  if (!new_state) {
    perror("malloc buffer state");
    exit(1);
  }
  new_state->mem_buffer_ptr = NULL;
  new_state->mem_buffer_size = 0;
  new_state->buffer_stream =
      open_memstream(&new_state->mem_buffer_ptr, &new_state->mem_buffer_size);
  if (!new_state->buffer_stream) {
    perror("open_memstream");
    free(new_state);
    exit(1);
  }
  new_state->prev = buffer_stack;
  buffer_stack = new_state;

  suppress_print++;
}

void reset_buffer(void) {
  /* Unwind the entire stack */
  while (buffer_stack) {
    if (buffer_stack->buffer_stream)
      fclose(buffer_stack->buffer_stream);
    if (buffer_stack->mem_buffer_ptr)
      free(buffer_stack->mem_buffer_ptr);
    BufferState *prev = buffer_stack->prev;
    free(buffer_stack);
    buffer_stack = prev;
  }
  suppress_print = 0;
}

char *stop_buffering(void) {
  if (mode != MODE_C_TO_RUN)
    return NULL;

  if (suppress_print > 0) {
    suppress_print--;
  }

  /* Pop the top buffer */
  if (buffer_stack) {
    BufferState *top = buffer_stack;

    if (top->buffer_stream)
      fclose(top->buffer_stream);
    char *ret = top->mem_buffer_ptr;
    /* don't free ptr, caller owns it */

    buffer_stack = top->prev;
    free(top);

    return ret;
  }
  return NULL;
}

void append_buffer(const char *s) {
  if (buffer_stack && buffer_stack->buffer_stream) {
    fprintf(buffer_stack->buffer_stream, "%s", s);
  }
}

void print_str(const char *s) {
  if (in_discovery_pass)
    return;
  if (suppress_print > 0) {
    append_buffer(s);
  } else {
    printf("%s", s);
  }
}

void print_token(const char *t) { print_str(t); }
