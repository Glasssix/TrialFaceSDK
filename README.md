# Glasssix TrialFaceSDK
Document, binary module, example and billboard for face SDK of Trial version

## Glasssix TrialFaceSDK 

[![License](https://img.shields.io/badge/license-BSD-blue.svg)](LICENSE)

### Description

**Glasssix TrialFaceSDK** contains three key parts, i.e., **Longinus(Face Detect and Alignment)**, **Gaius(Feature Extractor)** and **Irisvian(Face Search)**. It can run in Android OS, Windows and Linux.

* Longinus(Face Detect and Alignment). See [Longinus](./doc/Longinus.md) for more details. 

* Gaius(Feature Extractor). See [Gaius](./doc/Gaius.md) for more details.

* Irisvian(Face Search). See [Irisvian](./doc/Irisvian.md) for more details. 

This trial face SDK is developed by GLASSSIX. The open source is now released under BSD-2 license (see [LICENSE](LICENSE) for details), which means the codes can be used freely for both acedemic purpose and industrial products.


### Test Report

根据实际使用场景，在x86平台选取1K,2K,5K,10K,20K,50K,100K,200K,500K的基础数据量(baseNum)分别进行测试（K表示1000条）。待查询数据量(queryNum)为基础数据量(baseNum)的十分之一,对每条待查询数据,返回10个相似度最高的结果。将返回的10个结果与通过高耗时暴力搜索方法找到的10个准确值进行对比，计算得到准确率。再用执行搜索任务的总时间除以查询数据量(queryNum)，得到每条数据的搜索时间。

\subsection{CPU: Intel i7-8700K}
测试平台基本信息如表\ref{tab:basic-info-i7-8700k}所示。
\begin{table}[H]
	\caption{基本信息}
	\label{tab:basic-info-i7-8700k}
	\begin{center}
		\begin{tabular}{lc}
			\multicolumn{1}{c}{\bf 细节}  &\multicolumn{1}{c}{\bf 描述}
			\\ \hline \\
			操作系统         &Windows 10 企业版 64位 \\
			处理器           &Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz \\
			处理器核心数     &6核12线程 \\
			内存             &32GB \\
			编译器           &MSVC 19.5 \\
			OpenMP           &开启 \\
			SIMD指令集       &AVX2 \\
		\end{tabular}
	\end{center}
\end{table}


\begin{table}[H]
	\caption{i7-8700k测试}
	\label{tab:i7-8700k}
	\begin{center}
		\begin{tabular}{ccccc}
			\multicolumn{1}{c}{\bf baseNum}  & \tabincell{cc}{\multicolumn{2}{c}{\bf buildTime(s)} \\ \bf 128d & \bf 512d} & \tabincell{cc}{\multicolumn{2}{c}{\bf searchTime(ms)} \\ \bf 128d & \bf 512d} & \tabincell{cc}{\multicolumn{2}{c}{\bf accuracy(\%)} \\ \bf 128d & \bf 512d} & \tabincell{cc}{\multicolumn{2}{c}{\bf peakMemory((MB)} \\ \bf 128d & \bf 512d}
			\\ \hline \\
			1k & \tabincell{cc}{0.080 & 0.166} & \tabincell{cc}{0.010 & 0.010} & \tabincell{cc}{100 & 100} & \tabincell{cc}{6 & 13}\\
			2k & \tabincell{cc}{0.141 & 0.327} & \tabincell{cc}{0.015 & 0.020} & \tabincell{cc}{100 & 100} & \tabincell{cc}{11 & 23}\\
			5k & \tabincell{cc}{0.493 & 1.310} & \tabincell{cc}{0.020 & 0.018} & \tabincell{cc}{99.92 & 100} & \tabincell{cc}{22 & 55}\\
			10k & \tabincell{cc}{0.828 & 2.686} & \tabincell{cc}{0.009 & 0.032} & \tabincell{cc}{100 & 99.93} & \tabincell{cc}{41 & 86}\\
			20k & \tabincell{cc}{1.733 & 6.046} & \tabincell{cc}{0.013 & 0.059} & \tabincell{cc}{99.96 & 99.95} & \tabincell{cc}{68 & 174}\\
			50k & \tabincell{cc}{4.845 & 18.949} & \tabincell{cc}{0.024 & 0.092} & \tabincell{cc}{99.56 & 99.95} & \tabincell{cc}{177 & 499}\\
			100k & \tabincell{cc}{20.261 & 58.221} & \tabincell{cc}{0.031 & 0.138} & \tabincell{cc}{99.80 & 99.80} & \tabincell{cc}{375 & 820}\\
			200k & \tabincell{cc}{71.380 & 160.246} & \tabincell{cc}{0.046 & 0.182} & \tabincell{cc}{99.95 & 99.75} & \tabincell{cc}{753 & 1674}\\
			500k & \tabincell{cc}{221.486 & 563.454} & \tabincell{cc}{0.070 & 0.215} & \tabincell{cc}{98.85 & 99.15} & \tabincell{cc}{2008 & 3597}\\
		\end{tabular}
	\end{center}
\end{table}

### Contact Info

If you have any problem on Glasssix TrialFaceSDK, please contact us by sending email to inlmouse@glasssix.com.
If Glasssix TrialFaceSDK can not meet your business needs, please contact business@glasssix.com for business cooperation. For more AI services, please visit GLASSSIX official website: http://www.facebeacon.com.


### Other Documentation

* [SeetaFace2 Detection](./FaceDetection/README.md)
* [SeetaFace2 Alignment](./FaceAlignment/README.md)
* [SeetaFace2 Identification](./FaceIdentification/README.md)
* [SeetaFace2 Cropper](./FaceCropper/README.md)

### Download links

* [Attachment](./attachment/README.md)
