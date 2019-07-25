
## Face Recognition V1.0(TrialFaceSDK)
### Capability Introduction
#### Interface Capability
- **Face Recognition**: input face image of 3*128*128(channels * height * width), extract 128-dimension feature vector.
#### Dependencied
- **CPU**: MSVCP140、VCRUNTIME140
### Invoke Method
#### Example Code：extract 128-dimension feature vector
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

#### Class Description: Gaius
##### Member Function`void GaiusFeature(int device);`
Capability: set device(do not support GPU in TrialFaceSDK)

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|device|int|`<0`<br>`>=0`|use cpu<br>use gpu numbered by 'device'| |

##### Member Function`std::vector<std::vector<float>> Forward(const float* inputData, int num, int order = 0);`
Capability: extract 128-dimension feature vector

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|inputData|`const float*`|user input|face image data||
|num|int|`>0`|number of face images| |
|order|int||array of face image data:NCHW/NHWC|order=0(NCHW),otherwise(NHWC)|

- Return Value
`std::vector<std::vector<float>>`, 128-dimension face feature vector, outer size of vector is the number of face images, inner size of vector is 128.

#### Gaius Performance
Test one 3*128*128(channels * height * width) face image on platform i7-8700K, loop 1000 times and calculate average extractTime. 

Item | Description
:-:|:-:
Operating System | Windows 10 Enterprise 64bit |
Processor | Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz |
Core and Thread | 6 Cores and 12 Threads |
RAM | 32GB |
Compiler | MSVC 19.5 |
OpenMP | Yes |
SIMD Instruction Set | AVX2 |
extractTime(ms) | 54.191 |