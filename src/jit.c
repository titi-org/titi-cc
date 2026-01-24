#define _GNU_SOURCE
#include "cc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

/* ArgList helpers (internal) */
static void arglist_reset(ArgList *list) {
  list->count = 0;
  list->args[0] = NULL;
}

static void arglist_add(ArgList *list, char *arg) {
  if (list->count < MAX_ARGS - 1) {
    list->args[list->count++] = arg;
    list->args[list->count] = NULL;
  } else {
    fprintf(stderr, "Error: Too many arguments\n");
    exit(1);
  }
}

static int handle_jit_run(int mem_fd, char **environ) {
#ifdef __linux__
  pid_t pid = fork();
  if (pid == 0) {
    char *args[] = {"jit_run", NULL};
    fexecve(mem_fd, args, environ);
    perror("fexecve");
    exit(1);
  } else if (pid > 0) {
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
      return WEXITSTATUS(status);
    return 1;
  } else {
    perror("fork");
    return 1;
  }
#else
  (void)mem_fd;
  (void)environ;
  fprintf(stderr, "JIT run not supported on this platform.\n");
  return 1;
#endif
}

/* top_parse declared in cc.h */

static int handle_jit_compilation(const char *cc_bin, ArgList *cc_args,
                                  int *mem_fd_out) {
#ifndef __linux__
  (void)cc_bin;
  (void)cc_args;
  (void)mem_fd_out;
  fprintf(stderr, "JIT compilation not supported on this platform.\n");
  return 1;
#else
  int mem_src_fd = memfd_create("jit_source", 0);
  if (mem_src_fd == -1) {
    perror("memfd_create source");
    return 1;
  }

  int mem_bin_fd = memfd_create("jit_binary", 0);
  if (mem_bin_fd == -1) {
    perror("memfd_create binary");
    close(mem_src_fd);
    return 1;
  }

  /* Add output flag to cc_args pointing to the binary memfd */
  char *out_flag;
  safe_asprintf(&out_flag, "/proc/self/fd/%d", mem_bin_fd);
  arglist_add(cc_args, strdup("-o"));
  arglist_add(cc_args, out_flag);

  /* Redirect stdout to mem_src_fd */
  int orig_stdout = dup(STDOUT_FILENO);
  if (dup2(mem_src_fd, STDOUT_FILENO) == -1) {
    perror("dup2 mem_src_fd");
    return 1;
  }

  print_specialized_preamble();

  yyscan_t scanner;
  if (top_lex_init(&scanner)) {
    perror("yylex_init jit");
    return 1;
  }
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror(filename);
    top_lex_destroy(scanner);
    return 1;
  }
  top_set_in(f, scanner);
  int res = top_parse(scanner, NULL);
  if (res == 0) {
    emit_all_specialized_code();
  }
  fclose(f);
  top_lex_destroy(scanner);
  reset_specialized_code();

  fflush(stdout);
  dup2(orig_stdout, STDOUT_FILENO);
  close(orig_stdout);

  if (res != 0) {
    fprintf(stderr, "Parser failed with code %d\n", res);
    close(mem_src_fd);
    close(mem_bin_fd);
    return res;
  }

  int pipe_src[2];
  if (pipe(pipe_src) == -1) {
    perror("pipe");
    return 1;
  }

  pid_t cc_pid = fork();
  if (cc_pid == 0) {
    close(pipe_src[1]);
    dup2(pipe_src[0], STDIN_FILENO);
    close(pipe_src[0]);

    execvp(cc_bin, cc_args->args);
    perror("execvp");
    _exit(1);
  }

  close(pipe_src[0]);
  lseek(mem_src_fd, 0, SEEK_SET);
  char buf[4096];
  ssize_t n;

  /* Debug: save to file */
  FILE *debug_f = fopen("/tmp/jit_source.c", "w");
  if (!debug_f) {
    perror("fopen /tmp/jit_source.c");
    // Continue without writing to debug file if it fails
  }

  while ((n = read(mem_src_fd, buf, sizeof(buf))) > 0) {
    if (debug_f) {
      if (fwrite(buf, 1, n, debug_f) != (size_t)n) {
        perror("fwrite to /tmp/jit_source.c");
        fclose(debug_f);
        debug_f = NULL; // Prevent further attempts to write
      }
    }
    if (write(pipe_src[1], buf, n) != n) {
      perror("write to cc");
      break;
    }
  }
  if (debug_f) {
    fclose(debug_f);
  }
  close(pipe_src[1]);

  int status_cc;
  waitpid(cc_pid, &status_cc, 0);
  int compile_res = (WIFEXITED(status_cc)) ? WEXITSTATUS(status_cc) : 1;

  if (compile_res != 0) {
    fprintf(stderr, "Compilation failed code %d\n", compile_res);
    close(mem_src_fd);
    close(mem_bin_fd);
    return 1;
  }
  close(mem_src_fd);
  *mem_fd_out = mem_bin_fd;
  return 0;
#endif
}

int jit_execute(const char *cc_bin, int argc, char **argv,
                int arg_start_index) {
  ArgList cc_args;
  arglist_reset(&cc_args);
  arglist_add(&cc_args, strdup(cc_bin));
  arglist_add(&cc_args, strdup("-x"));
  arglist_add(&cc_args, strdup("c"));
  arglist_add(&cc_args, strdup("-"));
  for (int i = arg_start_index; i < argc; i++) {
    arglist_add(&cc_args, argv[i]);
  }

  int mem_fd = -1;
  int res = handle_jit_compilation(cc_bin, &cc_args, &mem_fd);
  if (res == 0 && mem_fd != -1) {
    res = handle_jit_run(mem_fd, environ);
    close(mem_fd);
  }
  return res;
}
