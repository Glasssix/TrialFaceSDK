# Glasssix TrialFaceSDK
Document, binary module, example and billboard for face SDK of Trial version

## Glasssix TrialFaceSDK 

[![License](https://img.shields.io/badge/license-BSD-blue.svg)](LICENSE)

### Features

- Light Weighted. The package size of Windows(C++) edition is less than 10MB(9.91MB).
- Dependency Free. No third-party library dependencies, does not rely on BLAS / NNPACK or any other computing framework.
- Fast and Accurate. We designed our algorithm carefully, and adopt accelerating technique such as OpenMP, SIMD.
- Powerful. We provide many interfaces in TrialFaceSDK, they can meet requirements in different use cases.
- Clear User Guidance. Example code and Interface illustration are accessible in [Example](./x86/Windows/C++/README.md), [Longinus](./doc/Longinus_Ch.md), [Gaius](./doc/Gaius_Ch.md), [Irisvian](./doc/Irisvian_Ch.md).
- Excellent Compatibility. Glasssix TrialFaceSDK can work on different platforms: Windows(64bit), Linux(64bit), ARM.
- Multi-Lauguage Support. We provide C++, C#, Java edition for different purpose.

### Description

**Glasssix TrialFaceSDK** contains three key parts, i.e., **Longinus(Face Detect and Alignment)**, **Gaius(Feature Extractor)** and **Irisvian(Face Search)**. It can run in Android OS, Windows and Linux.

* Longinus(Face Detect and Alignment). An extremely fast face detection and alignment library(with C++/CLI wrapper).See [Longinus](./doc/Longinus_Ch.md) for more details. 

* Gaius(Feature Extractor). A light weighted CNN implementation(with C++/CLI wrapper), aim at face feature extraction.See [Gaius](./doc/Gaius_Ch.md) for more details.

* Irisvian(Face Search). An Extremely Fast Approximate Nearest Neighbor Search library. See [Irisvian](./doc/Irisvian_Ch.md) for more details. 

This trial face SDK is developed by GLASSSIX. The open source is now released under BSD-2 license (see [LICENSE](LICENSE) for details), which means the codes can be used freely for both acedemic purpose and industrial products.

### Other Documentation

#### For Chinese:
* [Example](./x86/Windows/C++/README.md)
* [Longinus](./doc/Longinus_Ch.md)
* [Gaius](./doc/Gaius_Ch.md)
* [Irisvian](./doc/Irisvian_Ch.md)

#### For English:
* [Example](./x86/Windows/C++/README.md)
* [Longinus](./doc/Longinus_Eng.md)
* [Gaius](./doc/Gaius_Eng.md)
* [Irisvian](./doc/Irisvian_Eng.md)

### Download links
* [Windows](./x86/Windows). Compiled with Visual Studio 2017.
* [Linux](./x86/Linux). Compiled with GCC 7.4.

## Contact Info

If you have any problem on Glasssix TrialFaceSDK, please contact us by submitting issue, we will respond as soon as possible.
Glasssix TrialFaceSDK do not support GPU, if you are interested in more powerful GPU edition, please contact us.
If Glasssix TrialFaceSDK can not meet your business needs, please contact business@glasssix.com for business cooperation. 
For more AI services, please visit GLASSSIX official website: http://www.glasssix.com/.

## Contributors

- Glasssix Research: [J. Zhang](https://github.com/fengye2two)

