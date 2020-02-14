## 人脸识别V1.0(TrialFaceSDK)
### 接口功能
>人脸识别: 输入3*128*128的图片，提取图片中人脸的128维(gaius)特征值
>#### 速览: 
| 核心函数 | 功能  |  返回值  |
|  :--------:   |  :--------:  | :--------:  |
| float *Gaiunia_Forward   | 提取图片中128维人脸特征数据  |  int,检测出的人脸个数, >=0     |

#### 示例代码
```c
#include <iostream>
#include "gaius_c.hpp"
#include <opencv2/opencv.hpp>

using namespace glasssix;
using namespace glasssix::gaius;

int main()
{
int num=5;

//定义一个保存多张图片的容器
std::vector<cv::Mat> src_images;

//读取一组图片并保存至容器中
for(int i=0;i<num;i++)
{
//临时存储1*3*128*128(图片数 * 通道数 * 图高 * 图宽)的图片
cv::Mat temp = cv::imread("D:/" + std::to_string(i) + ".jpg");
src_images.push_back(temp);
}

//获取并保存图片高度，宽度和通道值。
unsigned width = src_images[0].cols;//128
unsigned height = src_images[0].rows;//128
unsigned channels = src_images[0].channels();//3

//动态分配num张图片内存空间（num=5）
unsigned char *faceData = new unsigned char[num * width * height * channels];

//保存图片至已分配空间
for(int i=0;i<num;i++)
{
memcpy(faceData+i*width * height * channels,src_images[i].data,width * height * channels*sizeof(unsigned char));
}

//此人脸识别开发包，不支持使用GPU
//设备号小于0，使用CPU；其他情形根据设备号使用该号GPU，默认值-1
int device = -1;

//order==0(NCHW),others(NHWC), 默认值0.
int order = 1;

//得到一个GaiusFeature类的实例
GaiusFeature *gaius_instance=GaiusFeature *Gaiunia_NewInstance(int device);

//提取128维人脸特征值并保存至features128指向地址;
float *features128=Gaius_Forward(gaius_instance, faceData, int num, int order);

//释放一个GaiusFeature类的实例
void Gaius_ReleaseInstance(gaius_instance);

//释放内存
delete[] features128;
delete[] faceData;

return 0;
}
```

#### 类名：Gaius
##### 成员函数 ：GaiusFeature *Gaiunia_NewInstance(int device);
##### 功能：得到一个GaiusFeature类的实例
##### 返回值：实例指针

##### 成员函数 ：void Gaiunia_ReleaseInstance(GaiusFeature *instance);
##### 功能：释放一个LonginusDetector类的实例

##### 成员函数 ：unsigned char *Gaiunia_getVersion();
##### 功能：获取Gaius版本
##### 返回值：返回版本字符串首地址

##### 成员函数 ：float *Gaiunia_Forward(GaiusFeature *instance,unsigned char *input_data,int num, int order );
##### 功能：提取图片中128维人脸特征数据
##### 返回值：返回提取到的n个128维人脸特征数据首地址

|参数|参数类型|值|说明|备注|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|instance|`GaiusFeature*`||GaiusFeature<br>实例的指针| |
|input_data| `unsigned char *`|用户输入|人脸图片数据||
|num| int |`>0`|人脸图片的数量||
|device|int|`<0`<br>`>=0`|使用cpu<br>使用设备号为<br>device的gpu|
|order|int|order=0(NCHW),否则(NHWC)|人脸数据的排列方式:[NCHW/NHWC](https://www.cnblogs.com/sunny-li/p/9630305.html)||



