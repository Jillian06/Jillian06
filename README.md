<div align="center">

# Jillian Yang

**Electrical Engineering @ University of Toronto**  
Machine Learning · Signal Processing · Embedded AI · Hardware–Software Co-Design

[![AI/ML Portfolio](https://img.shields.io/badge/AI%2FML-Portfolio-2563eb?style=flat-square)](https://github.com/Jillian06/Jillian06/tree/ai-ml-portfolio-2027)
[![GitHub](https://img.shields.io/badge/GitHub-Jillian06-181717?style=flat-square&logo=github)](https://github.com/Jillian06)

</div>

## About

I am an Electrical Engineering student at the University of Toronto interested in **applied machine learning, intelligent sensing, signal processing, and efficient hardware implementations**. My work spans unsupervised anomaly detection for industrial vibration signals, DSP/FPGA acceleration, safety-aware path planning, hardware-aware neural networks, and embedded systems.

I especially enjoy problems that require both **reliable data/model evaluation** and an understanding of the physical or computational system where an algorithm will be used.

> Seeking 12-month co-op / research opportunities beginning in **May 2027**.

## Selected work

| Project | Focus | Technologies |
|---|---|---|
| [**APS360 — Industrial Bearing Anomaly Detection**](projects/aps360-bearing-anomaly-detection/README.md) | Unsupervised fault detection using log-STFT vibration spectrograms; convolutional autoencoder, VAE extension, classical baselines, leakage-aware evaluation | **PyTorch, Python, CNN/CAE, STFT, scikit-learn** |
| [**ADC-Aware BFP FFT Accelerator**](https://github.com/Jillian06/fmcw-radar-bfp-fft) | 1024-point radix-2 FFT for FMCW radar; adaptive block-floating-point scaling and bit-accurate numerical/RTL verification | SystemVerilog, Python, FPGA, DSP |
| [**Autonomous Path Planning Research**](https://github.com/Jillian06/safe-astar-path-planning) | Safety-aware A* planning research with an IEEE conference publication; obstacle clearance and search-efficiency analysis | Algorithms, A*, Python |
| [**Spiking Neural Network Research**](https://github.com/Jillian06/neuromorphic-snn-research) | Hardware-aware neuromorphic computing, event-driven inference, resource-aware neural-network design | SNNs, Embedded AI, HW/SW Co-Design |
| **Embedded Robotic Systems** | Sensor integration, PWM/motor control, debugging and embedded hardware/software interfaces | STM32, C/C++, Sensors, PCB |

## Featured project — APS360

### Anomaly Detection in Industrial Machinery Using Autoencoders on Vibration Data

**Problem:** Bearing-fault examples can be much scarcer than normal-operation data. I investigated whether a model trained on **normal vibration signals only** could detect faults by measuring how poorly it reconstructs new signals.

**Pipeline**

```text
Raw vibration → resampling → source-file split → windowing
              → 128×128 log-STFT spectrograms
              → Convolutional Autoencoder (normal-only training)
              → reconstruction error → validation-calibrated threshold
              → normal / possible fault
```

**Methods and evaluation**
- Designed a PyTorch convolutional autoencoder with a 128-dimensional latent code, plus a VAE extension.
- Compared against One-Class SVM, Isolation Forest, Local Outlier Factor, and PCA-reconstruction baselines using vibration statistics.
- Used source-file-level splitting before windowing to reduce leakage and calibrated the anomaly threshold using normal validation data.
- Evaluated AUROC, average precision, accuracy, balanced accuracy, and reconstruction behavior.

**Reported CWRU experiment:** 286 normal training windows, 56 normal validation windows, and 1,444 test windows. The CAE achieved **AUROC 1.0000** on the project's selected held-out CWRU fault subset. This is a *dataset- and split-specific result*, not proof of real-world or cross-dataset generalization. External MFPT evaluation was planned; no MFPT result is claimed here.

[**Read the APS360 project case study →**](projects/aps360-bearing-anomaly-detection/README.md)

## Technical toolkit

**Programming:** Python · C · C++ · MATLAB  
**Machine Learning:** PyTorch · CNNs / Autoencoders · Unsupervised Learning · scikit-learn · Model Evaluation  
**Signal Processing:** STFT · FFT · Vibration Analysis · Fixed-Point DSP  
**Embedded / Hardware:** STM32 · SystemVerilog · Verilog/VHDL · FPGA · PCB · SWD  
**Tools:** Git · GitHub · Quartus · ModelSim · VS Code

## Publication

**B. Cao, Z. Yang, L. Yu, Y. Zhang**, “Research on the star algorithm for safe path planning,” *2023 IEEE International Conference on Control, Electronics and Computer Technology (ICCECT)*, pp. 105–109. [DOI](https://doi.org/10.1109/ICCECT57938.2023.10141167)

## Explore

- [APS360 bearing anomaly detection — project case study](projects/aps360-bearing-anomaly-detection/README.md)
- [FMCW adaptive BFP FFT — numerical and RTL reference work](https://github.com/Jillian06/fmcw-radar-bfp-fft)
- [Safety-aware A* — reproducible research implementation](https://github.com/Jillian06/safe-astar-path-planning)
- [Neuromorphic SNN research — documentation-first research notes](https://github.com/Jillian06/neuromorphic-snn-research)
- [All public repositories](https://github.com/Jillian06?tab=repositories)

<div align="center">

**Machine Learning × Signal Processing × Embedded Systems × Hardware Acceleration**

</div>
