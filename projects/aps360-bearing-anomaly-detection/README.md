# APS360 — Bearing Anomaly Detection for Industrial Condition Monitoring

**University of Toronto · Applied Machine Learning · Python / PyTorch / Signal Processing**

This project investigates an industrial engineering question: **Can an ML model flag unusual bearing vibrations without requiring a large labeled fault-training dataset?** The approach uses normal-only training and reconstruction error, with conservative evaluation practices.

## Engineering problem and why the result matters

Machinery diagnostics must handle raw sensor measurements, changing sampling rates, and expensive false alarms. A model's score is only useful when its preprocessing, threshold and validation conditions are explicit. This project therefore combined vibration-signal processing, unsupervised neural networks, classical baselines and error analysis.

## Reproducible processing workflow

```text
CWRU bearing signal files (.mat; normal and fault recordings)
  → sampling-rate harmonization to 12 kHz
  → source-recording-level split before overlapping windowing
  → 4096-sample windows (75% overlap)
  → Hann-windowed short-time Fourier transform (STFT)
  → normalized 128 × 128 log-magnitude spectrograms
  → PyTorch convolutional autoencoder (normal-only training)
  → spectrogram reconstruction mean squared error
  → threshold from normal validation data: mean + 3 standard deviations
  → normal / anomaly flag
```

**Engineering sanity checks:** harmonize time and frequency axes across recordings, prevent window leakage across partitions, monitor reconstruction errors rather than classification accuracy alone, and avoid using held-out fault labels to set operating thresholds.

## Models and comparisons

**Primary model — CAE:** three stride-2 convolutional encoder blocks and a 128-dimensional latent representation; a mirrored transposed-convolution decoder reconstructs the input spectrogram. Trained with Adam, scheduling and early stopping on normal data.

**Additional model — VAE:** evaluated as a probabilistic neural extension.

**Classical baselines:** One-Class SVM, Isolation Forest, Local Outlier Factor and PCA reconstruction error. Baselines used handcrafted waveform statistics (including RMS, kurtosis, crest factor, and peak-to-peak amplitude) for a useful comparison against learned spectrogram representations.

## Reported experiment (selected CWRU subset)

| Dataset partition | Number of windows |
|---|---:|
| Normal training | 286 |
| Normal validation | 56 |
| Test — normal and fault | 1,444 |

| Model | AUROC | Accuracy |
|---|---:|---:|
| **Convolutional autoencoder** | **1.0000** | **1.0000** |
| One-Class SVM | 1.0000 | 1.0000 |
| Local Outlier Factor | 1.0000 | 1.0000 |
| PCA reconstruction | 1.0000 | 0.9972 |
| Isolation Forest | 0.9808 | 0.8414 |
| VAE (extension) | 0.9410 | Not stated in the comparison table |

**Interpretation and limitations:** The near-perfect scores for the CAE **and** simple baselines suggest that fault patterns in this subset are relatively easy to separate. They do **not** establish superiority of deep learning, robustness across load/sensor configurations, or validation on external machines. The project outlined MFPT cross-dataset evaluation; no external-dataset result is claimed.

## How this experience transfers to engineering AI tools

| Practical task | Relevant project experience |
|---|---|
| Build Python/ML functionality | Spectrogram preprocessing, PyTorch CAE/VAE, scikit-learn baselines |
| Check data correctness | Sampling-rate harmonization, file-level splits and leakage avoidance |
| Validate outputs | Metrics, baseline comparison, reconstruction inspection, explicit limitations |
| Surface engineering context | Sensor units, data provenance, thresholds and operation assumptions |
| Communicate decisions | Documented model pipeline, evaluation design and engineering trade-offs |

A future engineer-facing application could expose **anomaly scores, underlying measurements, threshold logic, model version and review flags**. This is a proposed product direction, not a claim that an industrial web service, database-backed system or production deployment exists.

## Code and dataset note

This directory is a **technical case study based on the APS360 project report**, not the original full implementation repository. The published portfolio does not presently include the complete training notebook. Raw data remain with the CWRU dataset provider. Full reproducibility requires the sanitized project notebook, environment pinning and exact source-data manifests.

[← AI/ML engineering portfolio README](../../README.md) · [← Interactive portfolio site](https://jillian06.github.io/ai-ml/)
