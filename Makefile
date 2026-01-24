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
         -I$(SRC) -I$(inc) -I$(inc_gen)
# Grammar objects (modular)
MODULAR_OBJS = $(obj)/val.tab.o

# Generated objects
GEN_OBJS = $(obj)/cc.yy.o \
           $(obj)/parser.tab.o \
           $(MODULAR_OBJS)

# Object files
OBJS = $(obj)/main.o \
       $(obj)/symtab.o \
       $(obj)/buffer.o \
       $(obj)/expr-util.o \
       $(obj)/jit.o \
       $(obj)/supercompiler.o \
       $(obj)/state.o \
       $(obj)/context.o \
       $(obj)/bridge.o \
       $(GEN_OBJS)

all: tests

# Create directories
$(inc_gen) $(src_gen) $(obj) $(bin):
	@mkdir -p $@

# Deduplicated rule for Bison
$(src_gen)/%.tab.c $(inc_gen)/%.tab.h: $(SRC)/%.y | $(src_gen) $(inc_gen)
	$(YACC) $(YFLAGS) -o $(src_gen)/$*.tab.c --header=$(inc_gen)/$*.tab.h $<

# Flex rule
$(src_gen)/cc.yy.c $(inc_gen)/cc.yy.h: $(SRC)/scanner.l $(inc_gen)/parser.tab.h | $(src_gen) $(inc_gen)
	$(LEX) -o $(src_gen)/cc.yy.c --header-file=$(inc_gen)/cc.yy.h $<

$(GEN_OBJS): $(inc_gen)/cc.yy.h $(inc_gen)/parser.tab.h
$(MODULAR_OBJS): $(inc_gen)/cc.yy.h $(inc_gen)/parser.tab.h

# Compilation rules for source files
$(obj)/%.o: $(SRC)/%.c | $(obj)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilation rules for generated sources
$(obj)/%.o: $(src_gen)/%.c | $(obj)
	$(CC) $(CFLAGS) -c -o $@ $<

# Linking
$(RUN_CC_TARGET): $(OBJS) | $(bin)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Explicit dependencies
$(obj)/main.o: $(SRC)/main.c $(SRC)/cc.h $(inc_gen)/parser.tab.h $(inc_gen)/cc.yy.h
$(obj)/cc.yy.o: $(src_gen)/cc.yy.c $(inc_gen)/parser.tab.h $(SRC)/cc.h
$(obj)/bridge.o: $(SRC)/bridge.c $(SRC)/val.h $(SRC)/expr.h $(SRC)/cc.h
$(OBJS): $(SRC)/val.h $(SRC)/expr.h $(SRC)/cc.h $(inc_gen)/parser.tab.h $(inc_gen)/cc.yy.h

tests: $(RUN_CC_TARGET)
	$(MAKE) -C tests -j$(nproc) RUN_CC=$(CURDIR)/$(RUN_CC_TARGET) BIN_DIR=$(CURDIR)/tests/bin RUN_CC_FLAGS="-I../$(SRC) -I../$(inc) -I../$(inc_gen)" CC=gcc

clean:
	rm -rf $(build) bin
	rm -f $(SRC)/*.o
	$(MAKE) -C tests -j$(nproc) clean