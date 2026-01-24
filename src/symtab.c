#define _POSIX_C_SOURCE 200809L
#include "cc.h"
#include "parser.tab.h"
#include "val.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Symbol Table (Minimal for parsing C) */
char **discovered_types = NULL;
int num_discovered_types = 0;
int discovered_types_cap = 0;

int is_type(const char *name) {
  for (int i = 0; i < num_discovered_types; i++) {
    if (streq(discovered_types[i], name))
      return 1;
  }
  return 0;
}

int register_type(const char *name) {
  if (is_type(name))
    return 0;
  if (num_discovered_types >= discovered_types_cap) {
    int new_cap = discovered_types_cap == 0 ? 16 : discovered_types_cap * 2;
    char **new_arr = realloc(discovered_types, new_cap * sizeof(char *));
    if (!new_arr)
      return -1;
    discovered_types = new_arr;
    discovered_types_cap = new_cap;
  }
  if (verbose)
    fprintf(stderr, "REGISTER TYPE: %s\n", name);
  discovered_types[num_discovered_types++] = strdup(name);
  return 1;
}

int get_symbol_table_size(void) { return num_discovered_types; }

void on_storage_class_typedef(void) { is_typedef = 1; }

static int typedef_stack[32];
static int typedef_ptr = 0;

void on_type_scope_enter(void) {
  if (typedef_ptr < 32) {
    typedef_stack[typedef_ptr++] = is_typedef;
  }
  is_typedef = 0;
}

void on_type_scope_exit(void) {
  if (typedef_ptr > 0) {
    is_typedef = typedef_stack[--typedef_ptr];
  }
}

void on_declarator(const char *name) {
  if (is_typedef) {
    register_type(name);
  }
}
