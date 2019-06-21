
## 人脸识别V1.0(TrialFaceSDK)
### 能力介绍
#### 接口能力
- **人脸识别**: 输入3*128*128的图片，提取图片中人脸的128维(gaius)特征值
#### 依赖项
- **CPU**: MSVCP140、VCRUNTIME140
### 调用方式
#### 示例代码一：人脸特征提取模块
```c++
#include <iostream>
#include "Gaius/GaiusFeature.hpp"
#include <opencv2/opencv.hpp>

using namespace glasssix;
using namespace glasssix::gaius;

int main()
{
	int num=5;
	std::vector<cv::Mat> src_images;
	for(int i=0;i<num;i++)
	{
	    //temp must be 1*3*128*128(num * channels * height * width)
	    cv::Mat temp = cv::imread("D:/" + std::to_string(i) + ".jpg");
		src_images.push_back(temp);
	}
	unsigned width = src_images[0].cols;//128
	unsigned height = src_images[0].rows;//128
	unsigned channels = src_images[0].channels();//3
	
	unsigned char *faceData = new unsigned char[num * width * height * channels];
	for(int i=0;i<num;i++)
	{
	    memcpy(faceData+i*width * height * channels,src_images[i].data(),width * height * channels*sizeof(unsigned char));
	}
	
	//do not support GPU in TrialFaceSDK
	int device = -1;//using CPU when device is less than zero, otherwise use the GPU numbered by 'device', device is set to -1 by default.
	int order = 1;//order==0(NCHW),others(NHWC), order is set to zero by default.
	
	gaius::GaiusFeature feat_extractor128(device);
	
	//128 dimension face features extracted
	std::vector<std::vector<float>> features128 = feat_extractor128.Forward(faceData, num, order);
	
	return 0;
}
```

#### Gaius类说明
##### 成员函数`void GaiusFeature(int device);`
功能: 设置128维人脸识别方式

|参数|参数类型|值|说明|备注|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|device|int|`<0`<br>`>=0`|使用cpu<br>使用设备号为device的gpu| |

##### 成员函数`std::vector<std::vector<float>> Forward(const float* inputData, int num, int order = 0);`
功能: 进行人脸识别，提取128维特征值

|参数|参数类型|值|说明|备注|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|inputData|`const float*`|用户输入|人脸图片数据||
|num|int|`>0`|人脸图片的数量| |
|order|int||人脸数据的排列方式:NCHW/NHWC|order=0(NCHW),否则(NHWC)|

- 返回值
`std::vector<std::vector<float>>`类型, vector包含了提取到的128维人脸特征信息，外层维度大小为人脸图片数量，内层维度大小为128。

##### 成员函数`std::vector<std::vector<float>> Forward(const unsigned char* inputData, int num, int order = 0);`
功能: 进行人脸识别，提取128维特征值

|参数|参数类型|值|说明|备注|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|inputData|`const unsigned char*`|用户输入|人脸图片数据||
|num|int|`>0`|人脸图片的数量| |
|order|int||人脸数据的排列方式:NCHW/NHWC|order=0(NCHW),否则(NHWC)|

- 返回值
`std::vector<std::vector<float>>`类型, vector包含了提取到的128维人脸特征信息，外层维度大小为人脸图片数量，内层维度大小为128。

#### Gaius性能表现
在i7-8700K平台使用1张3*128*128（通道数*高度*宽度）的人脸图片进行测试，循环1000次计算得到平均提取时间。

项目 | 描述
:-:|:-:
操作系统 | Windows 10 企业版 64位 |
处理器 | Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz |
处理器核心数 | 6核12线程 |
内存 | 32GB |
编译器 | MSVC 19.5 |
OpenMP | 开启 |
SIMD指令集 | AVX2 |
提取时间(ms) |  54.191 |