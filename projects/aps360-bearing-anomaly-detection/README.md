# APS360 — Industrial Bearing Anomaly Detection

**University of Toronto | Applied Machine Learning**  
**Project:** Anomaly Detection in Industrial Machinery Using Autoencoders on Vibration Data  
**Focus:** Unsupervised learning · vibration sensing · signal processing · anomaly evaluation

## Motivation

Unexpected bearing faults create expensive industrial downtime. Fault examples are often scarce compared with normal operating data, so this project investigates **normal-only learning**: train a model to reconstruct healthy vibration patterns, and flag test signals with unusually high reconstruction error.

## End-to-end approach

```text
CWRU bearing vibration data (.mat)
   -> sampling-rate harmonization (12 kHz)
   -> source-file-aware train / validation / test split
   -> 4096-sample vibration windows
   -> Hann-windowed STFT
   -> normalized 128 x 128 log-magnitude spectrogram
   -> convolutional autoencoder
   -> reconstruction mean-squared error
   -> normal-validation threshold (mean + 3 sigma)
   -> anomaly flag
```

### Neural models

- **Convolutional Autoencoder (CAE):** three stride-2 convolutional encoder blocks, a 128-dimensional latent representation, and a transposed-convolution decoder. Training minimizes spectrogram reconstruction MSE on normal windows only.
- **Variational Autoencoder (VAE):** a probabilistic extension assessed against the main CAE.
- **Training:** PyTorch with Adam, learning-rate scheduling, early stopping and validation monitoring.

### Classical comparisons

Four unsupervised baselines were built on vibration-window statistics: One-Class SVM, Isolation Forest, Local Outlier Factor, and PCA reconstruction error. The feature set included RMS, kurtosis, crest factor, standard deviation, skewness, peak-to-peak amplitude and additional waveform statistics.

### Data leakage and evaluation

Split the source files *before* generating overlapping windows to prevent near-duplicate signals from leaking between sets. The anomaly threshold used **normal validation data**, not fault labels; faulty samples were used to evaluate detection behavior.

The reported experiment uses a CWRU subset with:

| Split | Windows |
|---|---:|
| Train (normal) | 286 |
| Validation (normal) | 56 |
| Test (normal + fault) | 1,444 |

## Reported results

The project's progress report includes the following measurements on its **selected held-out CWRU dataset**:

| Model | AUROC | Accuracy |
|---|---:|---:|
| CAE (primary) | **1.0000** | **1.0000** |
| One-Class SVM | 1.0000 | 1.0000 |
| Local Outlier Factor | 1.0000 | 1.0000 |
| PCA Reconstruction | 1.0000 | 0.9972 |
| Isolation Forest | 0.9808 | 0.8414 |
| VAE (extension) | 0.9410 | Not reported in comparison table |

**Interpretation:** Several simple baselines also performed nearly perfectly on this particular fault subset. This result supports the feasibility of anomaly detection on these signals, but **does not demonstrate that the CAE outperforms all classical baselines or generalizes to new machines**. An external MFPT evaluation interface was proposed; cross-dataset performance should not be claimed without executing and reporting that evaluation.

## Engineering highlights

- End-to-end connection between accelerometer data, frequency-domain preprocessing, neural reconstruction, and anomaly decisions.
- Careful handling of heterogeneous original sampling rates (48 kHz and 12 kHz).
- Comparison of neural and non-neural detection approaches using identical evaluation splits.
- Investigation of reconstruction-error maps and fault-relevant frequency structure.
- Reported metrics include AUROC, average precision, balanced accuracy, and accuracy.

## Technology

Python · PyTorch · scikit-learn · NumPy · STFT · CNNs · Autoencoders · Anomaly Detection · Statistical Model Evaluation

## Source and reproducibility

This page is a **technical case study** based on the author's APS360 project report; it is **not a claim that a complete implementation is hosted in this profile repository**. The original project notebook and any data-dependent runtime dependencies should be reviewed and sanitized before publication. The CWRU data belong to their respective dataset provider and should be downloaded from the authoritative source.

[Back to the AI/ML portfolio](../../README.md)
