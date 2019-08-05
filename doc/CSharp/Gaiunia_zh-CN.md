
## 人脸识别 V1.0（TrialFaceSDK）
### 能力介绍
#### 接口能力
- **人脸识别**：输入 3 \* 128 \* 128 的图片，提取图片中人脸的 128 维（Gaius）特征值。
#### 依赖项
- **CPU**：
   - MSVCP141
   - VCRUNTIME141
   - .Net Framework 4.6.2
### 调用方式
#### 示例代码一：人脸特征提取模块
```C#
using System;
using System.Drawing;
using glasssix.gaius;

internal class Program
{
	static void Main(string[] args)
	{
      // The size of the bitmap must be 128x128.
      var bitmap = Bitmap.FromFile(@"D:\body.png");

      using (var extractor = new Gaiunia(-1))
      {
         // Fetch the feature vector.
         var feature128 = extractor.ExtractBitmapOutputs(bitmap);
      }
	}
}
```

#### ```Gaiunia``` 类
##### 构造函数 ```public Gaiunia(int device)```
功能：创建一个 Gaiunia 类的实例，由用户指定参与运算的物理设备。

|参数|参数类型|值|说明|备注|
|:---:|:---:|:---:|:---:|:---:|
|device|```int```|`<0`<br>`>=0`|使用 CPU 作为物理设备<br>使用设备号为 device 的 GPU 作为物理设备| |

##### 方法 ```public float[] ExtractBitmapOutputs(Bitmap[] imgData)```
功能：进行人脸识别，提取 128 维特征值。

|参数|参数类型|值|说明|备注|
|:---:|:---:|:---:|:---:|:---:|
|imgData|```Bitmap[]```|用户输入|要提取特征值的图片数组||

- 返回：```float[]``` 类型，其中包含提取出的 128 维人脸特征信息，按图片输入顺序连续存储。

##### 方法 ```static float CosineDistanceProb(float[] feature1, float[] feature2)```
功能：工具方法，用于计算两个特征值的余弦距离。

|参数|参数类型|值|说明|备注|
|:---:|:---:|:---:|:---:|:---:|
|feature1|```float[]```|用户输入|第一个特征值||
|feature2|```float[]```|用户输入|第二个特征值||

- 返回：```float``` 类型，两个特征值的余弦距离。

#### Gaius 性能表现
在 i7-8700 K平台使用 1 张 3 \* 128 \* 128（通道数 \* 高度 \* 宽度）的人脸图片进行测试，共循环 1000 次计算得到平均提取时间。

|项目|描述|
|:---:|:---:|
操作系统 | Windows 10 企业版 64位 |
处理器 | Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz |
处理器核心数 | 6核12线程 |
内存 | 32GB |
编译器 | MSVC 19.5 |
OpenMP | 开启 |
SIMD指令集 | AVX2 |
提取时间（ms）|  54.191 |