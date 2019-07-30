## Face Recognition V1.0(TrialFaceSDK)
### Capability Introduction
#### Interface Capability
- **Face Recognition(Feature Extraction)**: input face image of 3\times 128\times 128(channels \times  height \times  width), extract 128-dimension feature vector.

### Invoke Method
#### Example Code：extract 128-dimension feature vector
```java
package com.glasssix;
import com.glasssix.Gaiulinya.Gaiulinya;

import org.opencv.core.*;
import org.opencv.highgui.HighGui;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;

public class Main {

    public static void main(String[] args) {
        System.loadLibrary("opencv_java400");
        //using CPU when device is less than zero, otherwise use the GPU numbered by 'device', device is set to -1 by default.
		int device = -1;
		//order==0(NCHW),others(NHWC), order is set to zero by default.
		int order = 1;
        //do not support GPU in TrialFaceSDK
        Gaiulinya extractor = new Gaiulinya(-1);
        Mat img1 = Imgcodecs.imread("../img/aligned_face1.jpg");
        Mat img2 = Imgcodecs.imread("../img/aligned_face2.jpg");

		float[][] feat1 = extractor.ForwardbyMetaData(encode2bytes(img1), 1, 1);
        float[][] feat2 = extractor.ForwardbyMetaData(encode2bytes(img2), 1, 1);

		System.out.println("The similarity of 2 images is " + Gaiulinya.CosineDistanceProb(feat1[0], feat[1]));
    }
}
```

#### Class Description: Gaiulinya
##### Member Function`void Gaiulinya(int device);`
Capability: set device(do not support GPU in TrialFaceSDK)

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|device|int|`<0`<br>`>=0`|use cpu<br>use gpu numbered by 'device'| |

##### Member Function`float[][] ForwardbyMetaData(byte[] data, int faceCount, int order);`
Capability: extract 128-dimension feature vector

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|data|byte[]|user input|face image data||
|num|int|`>0`|number of face images| |
|order|int||array of face image data:NCHW/NHWC|order=0(NCHW),otherwise(NHWC)|

- Return Value
`float[][]`, 128-dimension face feature vector, outer size of vector is the number of face images, inner size of vector is 128.

#### Gaiulinya Performance
Test one 3\times 128\times 128(channels \times  height \times  width) face image on platform i7-8700K, loop 1000 times and calculate average extractTime. 

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