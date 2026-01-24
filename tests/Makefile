SHELL := /bin/bash
BIN := ../build/bin

# Executable tests in runtime directory
RUNTIME_SRCS := $(filter-out %.dusko.c,$(wildcard runtime/*.c))
RUNTIME_TESTS := $(RUNTIME_SRCS:.c=)

# Parser tests: AST-dump only tests in parser/ subdirectories
PARSER_SRCS := $(filter-out %.dusko.c,$(wildcard parser/*/*.c))
PARSER_TESTS := $(PARSER_SRCS:.c=)

.PHONY: all clean runtime-tests parser-tests

all: parser-tests runtime-tests

# Runtime tests
runtime-tests: $(RUNTIME_TESTS)
	@echo "✓ All runtime tests passed"

# Parser tests: AST-dump comparison only (no execution)
parser-tests: $(PARSER_TESTS)
	@echo "✓ All parser tests passed"

CC ?= gcc
CLANG ?= clang
RUN_CC ?= $(BIN)/run-cc

TEST_FLAGS ?= -std=c2x -O3 -lm -I../src -Werror

$(RUNTIME_TESTS): %: %.c
	mkdir -p $(dir $(BIN)/$@)
	@echo "Testing $@..."
	@echo "[GCC Native]"
	$(CC) $< -o $(BIN)/$@-gcc $(TEST_FLAGS) && $(BIN)/$@-gcc > $(BIN)/$@.gcc.out
	@echo "[Clang Native]"
	$(CLANG) $< -o $(BIN)/$@-clang $(TEST_FLAGS) && $(BIN)/$@-clang > $(BIN)/$@.clang.out
	@echo "[run-cc with GCC]"
	$(RUN_CC) -cc $(CC) -R -I../src $< $(TEST_FLAGS) > $(BIN)/$@.run-gcc.out
	@echo "[run-cc with Clang]"
	$(RUN_CC) -cc $(CLANG) -R -I../src $< $(TEST_FLAGS) > $(BIN)/$@.run-clang.out
	@echo "Verifying outputs..."
	@diff $(BIN)/$@.run-gcc.out $(BIN)/$@.gcc.out
	@diff $(BIN)/$@.run-clang.out $(BIN)/$@.clang.out
	@diff $(BIN)/$@.run-gcc.out $(BIN)/$@.run-clang.out
	@echo "Comparing -ast-dump for $@..."
	@$(RUN_CC) -ast-dump -R -I../src $< > $(BIN)/$@.ast.out
	@if [ -f $@.dusko.c ]; then diff -buw $@.dusko.c $(BIN)/$@.ast.out; else echo "Warning: $@.dusko.c not found, skipping AST check"; fi

$(PARSER_TESTS): %: %.c
	mkdir -p $(dir $(BIN)/$@)
	@echo "Testing $@..."
	@$(RUN_CC) -ast-dump $< > $(BIN)/$@.ast.out 2>&1
	@if [ -f $@.dusko.c ]; then \
		diff -buw $@.dusko.c $(BIN)/$@.ast.out && echo "✓ $@ passed"; \
	else \
		echo "SKIP: $@ (no .dusko.c file)"; \
	fi

clean:
	git clean -Xdf
