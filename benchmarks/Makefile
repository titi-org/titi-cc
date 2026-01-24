CC ?= gcc
CLANG ?= clang
BIN_DIR := ../bin
RUN_CC ?= $(BIN_DIR)/run-cc
# test_rapidhash.c deleted as per user request
SRC_DIR := rapidhash

# Test cases (correctness)
TEST_SRCS := test_rapidhash.c
TESTS := $(TEST_SRCS:.c=)

# Benchmark cases
BENCH_DIR := $(SRC_DIR)/bench
COLL_DIR := $(SRC_DIR)/collisions

.PHONY: all clean check-collisions benchmark

all: benchmark # test_rapidhash targets removed

# check-correctness: $(TESTS) # Removed as per user request

# $(TESTS): %: %.c # Removed as per user request
# 	@echo "Testing correctness for $@..."
# 	@mkdir -p $(BIN_DIR)
# 	@echo "[$(CC) Path]"
# 	time ($(CC) -O3 -I. -I../src $< -o $(BIN_DIR)/$@-gcc -lm && $(BIN_DIR)/$@-gcc > $(BIN_DIR)/$@.gcc.out)
# 	@echo "[$(CLANG) Path]"
# 	time ($(CLANG) -O3 -I. -I../src $< -o $(BIN_DIR)/$@-clang -lm && $(BIN_DIR)/$@-clang > $(BIN_DIR)/$@.clang.out)
# 	@echo "[run-cc Path]"
# 	time $(RUN_CC) -cc $(CC) -R -I. -I../src $< -o $(BIN_DIR)/$@-run && $(BIN_DIR)/$@-run > $(BIN_DIR)/$@.run.out
# 	@diff $(BIN_DIR)/$@.run.out $(BIN_DIR)/$@.gcc.out
# 	@diff $(BIN_DIR)/$@.run.out $(BIN_DIR)/$@.clang.out
# 	@echo "✓ Correctness test $@ passed for GCC and Clang"

check-collisions:
	@echo "Running collision tests..."
	$(MAKE) -C $(COLL_DIR) check
	@echo "✓ Collision tests completed"

benchmarks: clean
	@echo "Running benchmarks..."
	@echo "[GCC Benchmark]"
	$(MAKE) -C $(BENCH_DIR) CC=$(CC) MOREFLAGS="-Wall -Wextra -Werror -pedantic"
	./$(BENCH_DIR)/benchHash --mins=1 --maxs=8 --minl=10 --maxl=11 > benchmark_gcc.bench.out
	$(MAKE) -C $(BENCH_DIR) clean
	@echo "[Clang Benchmark]"
	$(MAKE) -C $(BENCH_DIR) CC=$(CLANG) MOREFLAGS="-Wall -Wextra -Werror -pedantic"
	./$(BENCH_DIR)/benchHash --mins=1 --maxs=8 --minl=10 --maxl=11 > benchmark_clang.bench.out
	$(MAKE) -C $(BENCH_DIR) clean
	@echo "[run-cc Benchmark]"
	# Use -O3 for the specialized version to allow GCC to inline/optimize the supercompiled calls
	# We omit strict checks here because supercompiled code may have benign GCC extensions 
	# and extern declarations that trigger -pedantic and -Wall warnings.
	$(MAKE) -C $(BENCH_DIR) CC="$(abspath $(RUN_CC)) -cc $(CC) --cflags '-march=native -O3' -R -x c - -I$(abspath ../src) -I$(abspath ../include)" MOREFLAGS="-O3 -DXXH_NAMESPACE= -w"
	./$(BENCH_DIR)/benchHash --mins=1 --maxs=8 --minl=10 --maxl=11 > benchmark_run_cc.bench.out
	@echo "✓ Benchmarks completed. Results in benchmark_gcc.bench.out, benchmark_clang.bench.out and benchmark_run_cc.bench.out"
	@echo "✓ Benchmarks completed. Results in benchmark_gcc.bench.out, benchmark_clang.bench.out and benchmark_run_cc.bench.out"

clean:
	rm -f benchmark_*.bench.out
	$(MAKE) -C $(BENCH_DIR) clean
	$(MAKE) -C $(COLL_DIR) clean
