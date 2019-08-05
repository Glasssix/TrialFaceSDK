## Face Recognition V1.0(TrialFaceSDK)
### Capability Introduction
#### Interface Capability
- **Face Recognition**: Extracts the 128-dimensional feature vector (known as *Gaius*) of a 3 \* 128 \* 128 image containing at least one face.

#### Dependencies
- **CPU**：
   - MSVCP141
   - VCRUNTIME141
   - .Net Framework 4.6.2
### Examples
#### Example 1: Simple Usage
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

#### ```Gaiunia``` Class
##### Constructor ```public Gaiunia(int device)```
Description: creates a new instance with the specified device ID.

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