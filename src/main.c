#define _GNU_SOURCE
#include "cc.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

/* External Dependencies */
extern FILE *in;
extern int lineno;
extern void restart(FILE *in);

extern int get_symbol_table_size(void);
extern int register_type(const char *name);

/*****************************************************************************/
/*                            DRIVER & HELPERS                               */
/*****************************************************************************/

typedef struct {
  const char *cc_bin;
  char *input_file;
  int ast_dump;
  int arg_index;
} Options;

static void parse_options(int argc, char **argv, Options *opts) {
  extern int top_debug;

  opts->cc_bin = getenv("RUN_CC_BIN");
  if (!opts->cc_bin)
    opts->cc_bin = "gcc";
  opts->ast_dump = 0;
  opts->input_file = NULL;

  int i = 1;
  while (i < argc && argv[i][0] == '-') {
    const char *arg = argv[i];
    if (streq(arg, "-cc") && i + 1 < argc) {
      opts->cc_bin = argv[++i];
    } else if (streq(arg, "-ast-dump")) {
      opts->ast_dump = 1;
    } else if (streq(arg, "-v")) {
      verbose = 1;
      top_debug = 1;
    } else if (streq(arg, "-R")) {
      run_mode = 1;
      /* Skip -R and its argument if present */
      if (i + 1 < argc && argv[i + 1][0] != '-')
        i++;
    }
    i++;
  }

  if (i < argc)
    opts->input_file = argv[i++];
  opts->arg_index = i;
}

int main(int argc, char **argv) {
  Options opts;
  parse_options(argc, argv, &opts);

  if (!opts.input_file) {
    fprintf(stderr, "Usage: %s [options] <input_file> [compiler_args...]\n",
            argv[0]);
    return 1;
  }

  filename = opts.input_file;

  lex_init();

  yyscan_t scanner;
  if (top_lex_init(&scanner)) {
    perror("yylex_init");
    return 1;
  }

  /* First pass: Discovery */
  mode = MODE_DISCOVERY;
  in_discovery_pass = 1;
  suppress_print = 1;
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror(filename);
    return 1;
  }
  top_set_in(f, scanner);
  top_parse(scanner, NULL);
  fclose(f);

  /* Second pass: Transformation */
  mode = MODE_C_TO_RUN;
  in_discovery_pass = 0;
  suppress_print = 0;
  top_set_lineno(1, scanner);
  lex_init();
  f = fopen(filename, "r");
  if (!f) {
    perror(filename);
    return 1;
  }
  top_set_in(f, scanner);

  int final_res = 0;

  if (should_emit_run() && !opts.ast_dump) {
    /* JIT compilation and execution */
    final_res = jit_execute(opts.cc_bin, argc, argv, opts.arg_index);
  } else {
    /* Standard transformation pass for output/AST dump */
    print_specialized_preamble();
    if (top_parse(scanner, NULL) == 0) {
      emit_all_specialized_code();
    } else {
      fprintf(stderr, "Parse failed\n");
      final_res = 1;
    }
  }

  fclose(f);
  top_lex_destroy(scanner);

  return final_res;
}
