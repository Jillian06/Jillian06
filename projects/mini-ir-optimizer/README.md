# Mini IR Optimizer — Compiler Fundamentals in C++17

**Independent learning project created for a compiler engineering portfolio.** This is **not** LLVM, MLIR, Triton, SYCL, or a production compiler.

## Why this project

Explore core compiler middle-end ideas with working, inspectable C++:
- **Lexing / parsing** of a deliberately restricted straight-line language
- **Intermediate representation (IR)** using typed `MOV`, `ADD`, `SUB`, `MUL`, and `PRINT` instructions
- **Constant propagation and constant folding** in forward instruction order
- **Dead assignment elimination** via backward variable liveness
- **Reference interpretation** to compare program outputs before and after optimization
- **Overflow safeguards** using checked signed 64-bit arithmetic

## Quick start

Requires `g++` or `clang++` with C++17 support and Python 3 for the regression script.

```sh
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic main.cpp -o mini_ir
./mini_ir < sample.ir
./mini_ir --no-opt < sample.ir
python3 test.py
```

Input example (`sample.ir`):

```text
unused = 6 * 7
x = 3 + 4
y = x * 5
print y
```

Optimized IR:

```text
print 35
```

Printed output: `35`.

## Design and correctness

1. The parser checks identifier syntax and **use-before-definition** and rejects unsupported expressions.
2. A forward environment remembers constants and substitutes them into later instructions.
3. Folding only happens when checked 64-bit arithmetic is safe.
4. A backward liveness walk starts at every `print` and retains only assignments needed for observable output.
5. The test script runs both optimized and unoptimized modes and compares their printed results.

**Limitations:** no parentheses, nested expressions, conditionals, loops, SSA, CFG, alias analysis, code generation, GPU kernels, LLVM/MLIR integration, or realistic compile-time performance claims. Constant propagation does not attempt cross-block dataflow. This is a *teaching demonstrator* in one translation unit. The signed-overflow behavior is an explicit error, not wrapping arithmetic.

## Test cases

The regression script checks constant folding, dead assignments, reassignment, negative operands, multiple outputs, undefined variables, invalid syntax, and 64-bit overflow. Run `python3 test.py` after compilation to reproduce the checks.

[Back to compiler-oriented portfolio](../../README.md)
