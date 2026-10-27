<div align="center">

# Jillian Yang

**Electrical & Computer Engineering · University of Toronto**  
**C++ · Compiler Fundamentals · Algorithms · Computer Architecture · Performance & Verification**

[**Compiler Portfolio Site**](https://jillian06.github.io/intel-compiler/) · [**C++ IR Optimizer Demo**](projects/mini-ir-optimizer/README.md) · [**FPGA / FFT Research**](https://github.com/Jillian06/fmcw-radar-bfp-fft)

</div>

## About

I am a University of Toronto engineering student interested in how **programming languages, compilers, runtime systems, and computer architecture** translate algorithms into efficient execution on real hardware.

My strongest existing project evidence is in **bit-accurate numerical verification for FPGA/DSP**, **algorithm design**, and **applied machine learning**. To develop compiler-specific fundamentals, I also built a small independent C++17 intermediate-representation (IR) optimization exercise. It is deliberately scoped as an educational project—not an LLVM, MLIR, or Triton contribution.

**Seeking a 12–16 month internship beginning May 2027** · Toronto, Canada.

## Selected work — most relevant to compiler engineering

| Project | Why it is relevant | Technologies |
|---|---|---|
| **[Mini IR Optimizer (new C++17 exercise)](projects/mini-ir-optimizer/README.md)** | Simple straight-line IR, constant propagation/folding, backward liveness / dead assignment elimination, reference execution, tests | **C++17, IR, Optimization, Testing** |
| **[ADC-Aware BFP FFT Accelerator](https://github.com/Jillian06/fmcw-radar-bfp-fft)** | Fixed-point arithmetic, overflow analysis, bit-accurate Python↔RTL reference checks, accuracy/performance trade-offs | **SystemVerilog, Python, FPGA, DSP** |
| **[Safe A* Path Planning](https://github.com/Jillian06/safe-astar-path-planning)** | Graph algorithms, correctness and efficiency trade-offs, structured test cases, research-to-code translation | **Algorithms, Python, Testing** |
| **[APS360 — Bearing Anomaly Detection](projects/aps360-bearing-anomaly-detection/README.md)** | Model execution pipelines, numerical preprocessing, evaluation methodology and PyTorch familiarity | **PyTorch, Python, Numerical Computing** |
| **[Neuromorphic SNN Research](https://github.com/Jillian06/neuromorphic-snn-research)** | Hardware-aware computation and resource constraints; documentation-first research | **Hardware–software co-design** |

## Featured learning project — Mini IR Optimizer

This toy exercise explores a small slice of the compiler middle end:

```text
Straight-line assignment program
             ↓
Parsing and semantic validation
             ↓
Simple three-address-style IR
             ↓
Constant propagation + folding
             ↓
Backward liveness analysis
             ↓
Dead assignment elimination
             ↓
Reference evaluation and regression tests
```

Example:

```text
# Input                   # Optimized IR
unused = 6 * 7           print 35
x = 3 + 4
y = x * 5
print y
```

The optimizer preserves observable printed outputs on supported non-overflowing inputs. The implementation avoids silently folding signed-integer overflow; overflow is an explicit runtime error in the reference evaluator. **Scope:** no SSA, control-flow graphs, instruction selection, code emission, LLVM dialects, GPU kernels, or industrial compiler integration.

[**Read the compiler exercise →**](projects/mini-ir-optimizer/README.md)

## Why hardware-aware software interests me

On the **1024-point FMCW FFT** research project, I worked on dynamic range management, block-floating-point scaling and bit-accurate verification across Python and hardware implementations. The reported design improved SQNR by **24.31 dB** compared with fixed per-stage scaling in the documented experimental condition. This taught me to view performance and numerical correctness together—a useful mindset for backend optimization, compiler validation, and heterogeneous execution.

[**See FFT documentation and verification →**](https://github.com/Jillian06/fmcw-radar-bfp-fft)

## Technical background

**Languages:** C · C++ (coursework and self-directed practice) · Python · MATLAB · SystemVerilog  
**Foundations:** algorithms & data structures · computer organization · digital logic · finite-precision arithmetic  
**Engineering workflow:** Git / GitHub · automated tests · debugging · reproducible comparisons · technical documentation  
**AI / hardware:** PyTorch · FFT / DSP · FPGA · hardware-aware numerical analysis

**Currently learning, not claiming production experience:** LLVM/Clang, MLIR, Triton, SYCL, GPU kernel tiling, compiler pass infrastructure, and GPU runtime/offload systems.

## Publication

**B. Cao, Z. Yang, L. Yu, Y. Zhang**, “Research on the star algorithm for safe path planning,” *2023 IEEE International Conference on Control, Electronics and Computer Technology (ICCECT)*, pp. 105–109. [DOI](https://doi.org/10.1109/ICCECT57938.2023.10141167)

---

*This is a dedicated compiler-oriented Git branch. My original GitHub profile and other application-specific branches remain unchanged.*
