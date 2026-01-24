# run-cc Benchmark Results

This project benchmarks the `run-cc` supercompiler by using it as a specialized frontend for C compilation and comparing the results with standard `gcc` and `clang`.

## Overview

The benchmark uses the `rapidhash` project to verify that `run-cc` can correctly parse and compile a real-world C codebase with optimizations enabled, targeting POSIX environments.

## Findings

### Parser Compatibility
- **C99 Support**: Successfully handles C99 features like `for` loop declarations, designated initializers, and compound literals, enabling compatibility with modern libraries.
- **Preprocessor**: Handles complex macros and multi-line definitions.
- **Typedefs**: Correctly identifies and tracks custom types across multiple files.
- **Robustness**: The parser successfully processed all files in the `rapidhash` benchmark suite (approximately 20 files).

### Performance Comparison
Actual results from the latest benchmark run (Throughput):

| Throughput | run-cc | gcc | clang |
| :--- | :--- | :--- | :--- |
| Large Inputs (High) | ~37.3 GB/s | ~46.7 GB/s | ~35.6 GB/s |
| Small Inputs (1-8B) | ~375M ops/s | ~420M ops/s | ~465M ops/s |

## Supercompilation Improvements

Current supercompilation (via `run()`) can be further improved in the following areas:
- **TCO (Tail Call Optimization)**: Specializing recursive calls into loops during the specialization pass.
- **Dead Code Elimination**: More aggressive removal of branches that become constant after specialization.
- **Constant Folding**: Pre-calculating complex hash operations when some inputs are known.
- **SIMD Auto-vectorization**: Detecting patterns in specialized code that can be mapped to SIMD primitives more effectively than generic code.

## How to Run
To reproduce the benchmarks:
```bash
make benchmark
```
This will build all binaries and run them sequentially.
