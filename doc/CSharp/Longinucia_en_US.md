## Face Recognition V1.0 (TrialFaceSDK)
### Capability Introduction
#### Interface Capability
- **Face Recognition**: Extract the 128-dimensional feature vector (known as *Gaius*) of a 3 \* 128 \* 128 image containing at least one face.

#### Dependencies
- **CPU**：
   - MSVCP141
   - VCRUNTIME141
   - .Net Framework 4.6.2
### Examples
#### Example 1: Simple Usage
```C#
using System;
using glasssix::gaius;

internal class Program
{
	static void Main(string[] args)
	{

	}
}
```

#### ```Gaiunia``` Class
##### Constructor ```public Gaiunia(int device)```
Description: create a new instance with the specified device ID.

Parameters: 

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|device|int|`<0`<br>`>=0`|Sets the CPU as the physical device.<br>Sets the GPU as the physical device.| |

##### Method ```public float[] ExtractBitmapOutputs(Bitmap[] imgData)```
Description：extracts the 128-dimensional feature vectors of the input bitmaps.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|imgData|```Bitmap[]```|User Input|The input bitmaps||

- Returns: a ```float[]``` in which the feature vectors are arranged in the input order.

##### Method ```static float CosineDistanceProb(float[] feature1, float[] feature2)```
Description: calculates the cosine distance between ```feature1``` and ```feature2```.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|feature1|```float[]```|User Input|The first feature vector||
|feature2|```float[]```|User Input|The second feature vector||

- Returns: a ```float``` value which contains the cosine distance.

#### Gaius Performance
The following table reveals the testing result deduced by calculating the average time of 1,000-time extractions using a 3 \* 128 \* 128 (channels \* height \* width) face image on Platform i7-8700K.

|Item|Description|
|:---:|:---:|
Operating System | Windows 10 Enterprise 64bit |
Processor | Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz |
Core and Thread | 6 Cores and 12 Threads |
RAM | 32GB |
Compiler | MSVC 19.5 |
OpenMP | Yes |
SIMD Instruction Set | AVX2 |
Time of Extractions (ms) | 54.191 |


## Face Recognition V1.0(TrialFaceSDK)
### Capability Introduction
#### Interface Capability
- **Face Detection**：检测图片中人脸，并计算出人脸概率、人脸角度、关键点（眼、鼻、嘴）位置等信息。
#### Dependencies
- **CPU**：
   - MSVCP141
   - VCRUNTIME141
   - .Net Framework 4.6.2
### Examples
#### Example 1
```C#
using System;
using glasssix::gaius;

internal class Program
{
	static void Main(string[] args)
	{

	}
}
```

#### ```Longinucia``` Class
##### Constructor ```public Longinucia()```
Description: creates an instance.

##### Constructor ```public Longinucia(int width, int height)```
Description: creates an instance with the specified width and height in pixels.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|width|```int```|User Input|The width in pixels||
|height|```int```|User Input|The height in pixels||

##### Method ```public void set(DetectorType type, int device)```
Description: sets the method of detection.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|type|```DetectorType```|FRONTALVIEW<br>FRONTALVIEW_REINFORCE<br>MULTIVIEW<br> MULTIVIEW_REINFORCE|The values is arranged in descending order of speed.||
|device|int|```<0```<br>```>=0```|Sets the CPU as the physical device.<br>Sets the GPU as the physical device.| |

##### Method ```public List<FaceInfo> Face_Detect(Bitmap bmp, int min_size, float scale, int minNeighbors, bool useMultiThreads, bool doEarlyReject, bool doLandmark)```
Description: invokes face detection on the input grayscale bitmap and locates the faces.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|bmp|```Bitmap```|User Input|The grayscale bitmap||
|minSize|```int```|```>=24```|The smallest window size of detection|The rectangle size of a detected face is ```>= minSize``` .|
|scale|```float```|```> 1```|The scaling ratio of the image|Generally ```> 1.1```|
|minNeighbors|```int```|```>=0```|The candidate boxes around the face rectangle|Generally set to 3|
|useMultiThreads|```bool```|```true```<br>```false```|Multithreaded<br>Single-threaded|Only effecitve when the device is less than zero. The default is ```false``` .|
|doEarlyReject|```bool```|```true```<br>```false```|Does early rejections<br>Skips early rejections|Speeds up the detection when set to ```true``` with a decreasing quality; otherwise the opposite. The default is ```false``` .|

- Returns: a ```List<FaceInfo>``` which contains information about detected faces.

#### Longinus Performance
The following table reveals the testing results deduced by calculating the average time of 1,000-time extractions on three images (640 \* 480、1280 \* 720 and 1920 \* 1080), on Platform i7-8700K.

##### Platform Information
Item | Description
:-:|:-:
Operating System | Windows 10 Enterprise 64bit |
Processor | Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz |
Core and Thread | 6 Cores and 12 Threads |
RAM | 32GB |
Compiler | MSVC 19.5 |
OpenMP | Yes |
SIMD Instruction Set | AVX2 |


##### Test Results

Parameter: minSize=48, scale=1.2, minNeighbors=3, useMultiThreads=false, doEarlyReject=false

Detection Time (ms)：

Size | FRONTALVIEW | FRONTALVIEW_REINFORCE | MULTIVIEW | MULTIVIEW_REINFORCE
:-:|:-:|:-:|:-:|:-:
640 * 480 | 11.72 | 25.72 | 34.06 | 41.42 |
1280 * 720 | 26.14 | 45.44 | 69.09 | 85.07 |
1920 * 1080 | 76.59 | 122.38 | 155.89 | 186.86 |

![avatar](../640.jpg)
![avatar](../720.jpg)
![avatar](../1080.jpg)

Content Disclaimer: The test images are downloaded from the Internet and the copyright belongs to the original author. If there is any infringement, please contact me to delete the contents. Thank you.