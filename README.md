<div align="center">

# Jillian Yang

**Electrical Engineering | University of Toronto**  
**Applied Machine Learning · Engineering Software · Signal Processing · Hardware-Aware Verification**

[**AI / ML Engineering Portfolio**](https://jillian06.github.io/ai-ml/index.html) · [**Interactive Electrical Check**](https://jillian06.github.io/ai-ml/tools/rl-checker/) · [**GitHub Projects**](https://github.com/Jillian06?tab=repositories)

</div>

## About

I am an Electrical Engineering student at the University of Toronto interested in building **practical AI/ML tools for engineering problems**. My projects connect **Python and PyTorch**, physical signal processing, numerical validation, and efficient digital hardware.

I care about the engineering questions *around* a model: Where does its input data come from? Can a result be trusted? How is it tested? Can someone else reproduce the analysis or use the tool?

**Co-op availability:** 12 months starting **May 2027**. Interested in in-person R&D and engineering software teams in the Greater Toronto Area.

## Selected engineering work

| Project | Engineering problem & contribution | Stack |
|---|---|---|
| **[APS360: Bearing Fault Anomaly Detection](projects/aps360-bearing-anomaly-detection/README.md)** | Train a convolutional autoencoder on normal vibration spectrograms; assess anomalies using reconstruction error, careful data splitting, baselines, and transparent evaluation | **Python, PyTorch, STFT, scikit-learn** |
| **[ADC-Aware BFP FFT for FMCW Radar](https://github.com/Jillian06/fmcw-radar-bfp-fft)** | Design and evaluate numerical scaling for a 1024-point FFT, using numerical and RTL verification to check finite-precision behavior | **SystemVerilog, Python, DSP, FPGA** |
| **[Electrical R–L Checker — Web Prototype](https://jillian06.github.io/ai-ml/tools/rl-checker/)** | Build an engineer-facing interactive calculator with input validation, explicit units, physical equations, and a user-defined current-limit check. *Portfolio demonstration; not a reactor design tool.* | **HTML, CSS, JavaScript, circuit fundamentals** |
| **[Safe A* Path Planning](https://github.com/Jillian06/safe-astar-path-planning)** | Evaluate path-planning modifications with obstacle clearance and reproducible search tests; associated with an IEEE publication | **Python, algorithms, test design** |
| **[Neuromorphic SNN Research](https://github.com/Jillian06/neuromorphic-snn-research)** | Investigate low-power event-driven networks and hardware-aware implementation trade-offs; documentation-first research archive | **SNN concepts, embedded AI, HW/SW co-design** |
| **Embedded Robotic Systems** | Work with sensors, PWM/motor control, microcontrollers, and hardware/software interfaces | **STM32, C/C++, PCB, debugging** |

## A closer look: APS360 industrial anomaly detection

**Goal:** Identify unusual bearing-vibration patterns even when labeled faults are scarce.

```text
Vibration (.mat) → common sampling rate → file-level split
      → overlapping windows → 128×128 log-STFT spectrograms
      → PyTorch convolutional autoencoder (normal-only training)
      → reconstruction error → validation-only anomaly threshold
      → evaluation on held-out normal and fault examples
```

- Compared the CAE against a VAE extension and four classical methods: One-Class SVM, Isolation Forest, Local Outlier Factor, and PCA reconstruction.
- Split source recordings **before** overlapping window generation to reduce leakage risk.
- Tracked ranking metrics and operating-point metrics, not accuracy alone.
- In a selected **CWRU subset** (1,444 test windows), the CAE achieved **AUROC 1.0000**; simple baselines were similarly strong. **This does not demonstrate generalization to different machines or superior performance over all baselines.**
- Clear next validation step: independently collected measurements, operating-condition shifts, and error analysis.

[**See methods, results, and limitations →**](projects/aps360-bearing-anomaly-detection/README.md)

## Engineering software + physics checks

I am especially interested in workflows that make an engineering model **usable and verifiable**:

1. **Requirements and input contracts** — declare units, ranges, assumptions, and failure conditions.
2. **Model or calculation** — use Python/ML where data-driven methods help; use physics equations for analytical checks.
3. **Validation** — prevent data leakage, compare against baselines, test boundary cases, and question implausible outputs.
4. **Interfaces and documentation** — show relevant numbers, assumptions, warnings, and reproducible steps.

The **[R–L Checker](https://jillian06.github.io/ai-ml/tools/rl-checker/)** is a small new web prototype illustrating this workflow with ideal AC circuit calculations. It is **not** evidence of industrial air-core-reactor design work, and it does **not** contain an AI model.

## Technical toolkit

**Programming:** Python · C · C++ · MATLAB · JavaScript (portfolio prototype)  
**Machine learning:** PyTorch · convolutional autoencoders · unsupervised anomaly detection · scikit-learn · model evaluation  
**Signal processing:** STFT · FFT · fixed-point DSP · vibration features  
**Electrical / embedded:** circuit analysis · STM32 · FPGA · SystemVerilog · PCB · sensors  
**Engineering practices:** Git · unit testing · numerical sanity checks · documentation · reproducibility

**Currently exploring:** Flask-based engineering APIs, SQL-backed engineering records, and integrating ML predictions with circuit/electromagnetic validity checks. These are **development interests**, not claims of prior production deployment or transformer/reactor design experience.

## Publication

**B. Cao, Z. Yang, L. Yu, Y. Zhang**, “Research on the star algorithm for safe path planning,” *2023 IEEE International Conference on Control, Electronics and Computer Technology (ICCECT)*, pp. 105–109. [IEEE DOI](https://doi.org/10.1109/ICCECT57938.2023.10141167).

---

*This is a separate, role-oriented portfolio branch. The original GitHub profile and projects are unchanged.*
