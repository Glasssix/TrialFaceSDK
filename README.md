# Glasssix TrialFaceSDK

Glasssix TrialFaceSDK is a free SDK for face recognition without any restrictions. 

[![License](https://img.shields.io/badge/license-BSD-blue.svg)](LICENSE)

### Features

- Light Weighted. The package size of Windows(C++) edition is less than 10MB(9.91MB).
- Dependency Free. No third-party library dependencies, does not rely on BLAS / NNPACK or any other computing framework.
- Fast and Accurate. We designed our algorithm carefully, and adopt accelerating technique such as OpenMP, SIMD.
- Powerful. We provide many interfaces in TrialFaceSDK, they can meet requirements in different use cases.
- Clear User Guidance. Example code and interface illustration are accessible in [Documentations](./doc).
- Excellent Compatibility. Glasssix TrialFaceSDK can work on different platforms: Windows(64bit), Linux(64bit), ARM Linux(Coming soon) and Android(Coming soon).
- Multi-Lauguage Support. We provide C++, C#(Linux platform sopport will provide download after the official release of .Net Core 3.0), Java edition for different purpose.
- **Attention: All dynamic libraries in [x86](./x86) folder actually is compiled into x86-64 architecture. For some reason, 32-bit version will not be provided.**

### Description

**Glasssix TrialFaceSDK** contains three key parts, i.e., **Face Detect and Alignment**, **Feature Extractor** and **Face Search**.

The binary dynamic library(with documentation) names of each module in every programming language are listed as the following table.

| 	Langrage\\ Module Name	| Face Detect and Alignment | Face Feature Extractor | Face Feature Search |
| :-------: | :-------:| :------: | :------: |
| C++     	|  [Longinus](./doc/C++/Longinus_en-US.md)| [Gaius](./doc/C++/Gaius_en-US.md) | [Irisviel](./doc/C++/Irisviel_en-US.md) |
| C#   		|[Longinucia](./doc/CSharp/Longinucia_en-US.md)|[Gaiunia](./doc/CSharp/Gaiunia_en-US.md) | [Irisvian](./doc/CSharp/Irisvian_en-US.md) |
| Java  	|[Longimila](./doc/Java/Longimila_en-US.md)|[Gaiulinya](./doc/Java/Gaiulinya_en-US.md) | [Irisvika](./doc/Java/Irisvika_en-US.md) |

This trial face SDK is developed by GLASSSIX. The open source is now released under BSD-2 license (see [LICENSE](LICENSE) for details), which means the codes can be used freely for both acedemic purpose and industrial products.

### Other Documentation

* [C++ Example](./x86/Windows/C++/README.md)

### Download links
* [Windows](./x86/Windows). Compiled with MSVC 19.10.
* [Linux](./x86/Linux). Compiled with GCC 7.4.

## Contact Info

If you have any problem on Glasssix TrialFaceSDK, please contact us by submitting issue, we will respond as soon as possible.

Glasssix TrialFaceSDK do not support GPU, if you are interested in more powerful GPU edition, please contact us for a commercial license.

If Glasssix TrialFaceSDK can not meet your business needs(faster and more accurate algorithm or any other ancillary functions), please contact business@glasssix.com or ai@glasssix.com for business cooperation. 

For more AI services, please visit GLASSSIX official website: http://www.glasssix.com/.

## Contributors

- Glasssix Research: [J. Zhang](https://github.com/fengye2two)
- Glasssix Research: [Y. Zhang](https://github.com/zhangyifu2016)
- Glasssix Research: [M. Zhang](https://github.com/mingyu92)

## Acknowledgment

The work is supported by the Computer Science Foundation of GLASSSIX.

