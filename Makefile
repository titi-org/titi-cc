.PHONY: all clean tests

RUN_CC_TARGET = build/bin/run-cc
SRC = src
inc = include
build = build
inc_gen = $(build)/inc
src_gen = $(build)/src
obj = $(build)/obj
bin = $(build)/bin

CC = gcc
YACC = bison
LEX = flex
YFLAGS = -d -v

CFLAGS = -std=c2x -O3 -Wall -Wextra -Werror -pedantic \
         -I$(SRC) -I$(inc_gen) -Wno-unused-function

# Generated objects
GEN_OBJS = $(obj)/cc.yy.o \
           $(obj)/parser.tab.o

# Object files
OBJS = $(obj)/main.o \
       $(GEN_OBJS)

all: tests

# Create directories
$(inc_gen) $(src_gen) $(obj) $(bin):
	@mkdir -p $@

# Bison rule
$(src_gen)/parser.tab.c $(inc_gen)/parser.tab.h: $(SRC)/parser.y | $(src_gen) $(inc_gen)
	$(YACC) $(YFLAGS) -o $(src_gen)/parser.tab.c --header=$(inc_gen)/parser.tab.h $<

# Flex rule
$(src_gen)/cc.yy.c $(inc_gen)/cc.yy.h: $(SRC)/scanner.l $(inc_gen)/parser.tab.h | $(src_gen) $(inc_gen)
	$(LEX) -o $(src_gen)/cc.yy.c --header-file=$(inc_gen)/cc.yy.h $<

# Compilation rules for source files
$(obj)/main.o: $(SRC)/main.c $(inc_gen)/parser.tab.h $(inc_gen)/cc.yy.h | $(obj)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation rules for generated sources
$(obj)/%.o: $(src_gen)/%.c | $(obj)
	$(CC) $(CFLAGS) -c -o $@ $<

# Linking
$(RUN_CC_TARGET): $(OBJS) | $(bin)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

tests: $(RUN_CC_TARGET)
	echo "int x;" > tests/dummy_header_gen.c
	./$(RUN_CC_TARGET) -ast-dump tests/dummy_header_gen.c | sed -n '/\/\* START OF run_runtime.h \*\//,/\/\* END OF run_nat.h \*\//p' > tests/run_runtime.h
	rm tests/dummy_header_gen.c
	$(MAKE) -C tests -j$(nproc) RUN_CC=$(CURDIR)/$(RUN_CC_TARGET) BIN_DIR=$(CURDIR)/tests/bin CC=gcc

clean:
	rm -rf $(build) bin tests/run_runtime.h
	$(MAKE) -C tests clean
