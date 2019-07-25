## Face Detect V1.0(TrialFaceSDK)
### Capability Introduction
#### Interface Capability

- **Face Detect**: Detect face in images, and calculate possibility, angle, position of key points(eyes, nose, mouth)

### Invoke Method
#### Example Code 1

```java
package com.glasssix;
import com.glasssix.Longimila.DetectionType;
import com.glasssix.Longimila.FaceRect;
import com.glasssix.Longimila.FaceRectwithFaceInfo;
import com.glasssix.Longimila.Longimila;

import org.opencv.core.*;
import org.opencv.highgui.HighGui;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;

public class Main {
	public static void main(String[] args) {
		System.loadLibrary("opencv_java400");
		//do not support GPU in TrialFaceSDK
		//using CPU when device is less than zero, otherwise use the GPU numbered by 'device', device is set to -1 by default.
		int device = -1;
		Longimila detector = new Longimila(device);
		detector.set(DetectionType.FRONTALVIEW, -1);
		Mat img = Imgcodecs.imread("../img/exciting.png");
        Mat gray = new Mat();
        Imgproc.cvtColor(img, gray, Imgproc.COLOR_BGR2GRAY);
        FaceRect[] results_rects = detector.detectbyMetaData(encode2bytes(gray), gray.width(), gray.height(), 24, 1.2F, 3);
        for(int i = 0; i < results_rects.length; i++){
	        Imgproc.rectangle(img, new Rect(results_rects[i].x, results_rects[i].y,results_rects[i].width,results_rects[i].height), new Scalar(0,0,255));
		}
        HighGui.imshow("test", img);
        HighGui.waitKey();
	}
	
	public static byte[] encode2bytes(Mat img){
        byte[] buffer = new byte[img.cols() * img.rows() * img.channels()];
        img.get(0,0, buffer);
        return buffer;
    }
}
```

#### Class Description: Longimila 
##### Member Function`void set(DetectionType detectionType, int device);`
Capability: set detect method and device

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|detectionType|enum DetectionType|FRONTALVIEW<br>FRONTALVIEW_REINFORCE<br>MULTIVIEW<br> MULTIVIEW_REINFORCE||detect effect and time consuming both ascend|
|device|int|`<0`<br>`>=0`|use cpu<br>use gpu numberd by 'device'| |


##### Member Function`FaceRect[] detectbyMetaData(byte[] metadata, int width, int height, int minSize, float scale, int minNeighbors);`
Capability: detect and locate face in single-channel image

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|metadata|byte[]`|user input|address of single-channel image data| image data should store continuously|
|width|int|user input|width of single-channel image| N/A |
|height|int|user input|height of single-channel image| N/A |
|minSize|int|effect value`>=24`|smallest detect window size|detected face area`>=minSize`|
|scale|float|`>1`|expand or shrink ratio of image|`>1.05`|
|minNeighbors|int|`>=0`|candidate boxes around face area|3 by default|

- Return Value
`FaceRect[]`, FaceRect contains detected face area information

###### Struct Description: FaceRect

|Member Variable|Type|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|
|x|int|x coordinate of left-top corner| |
|y|int|y coordinate of left-top corner| |
|width|int|width of face area| |
|height|int|height of face area| |
|neighbors|int|number of candidate boxes around face area||
|confidence|double|possibility to be a face||



#### Example Code 2:

```java
package com.glasssix;
import com.glasssix.Longimila.DetectionType;
import com.glasssix.Longimila.FaceRect;
import com.glasssix.Longimila.FaceRectwithFaceInfo;
import com.glasssix.Longimila.Longimila;

import org.opencv.core.*;
import org.opencv.highgui.HighGui;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;

public class Main {
	public static void main(String[] args) {
		System.loadLibrary("opencv_java400");
		Mat img = Imgcodecs.imread("../img/exciting.png");
        Mat gray = new Mat();
        //transform color image to gray image
        Imgproc.cvtColor(img, gray, Imgproc.COLOR_BGR2GRAY);
        
        /*
		* Face Detection
		*/
	    //do not support GPU in TrialFaceSDK
		Longimila detector = new Longimila(device);
	    //using CPU when device is less than zero, otherwise use the GPU numbered by 'device', device is set to -1 by default.
	    int device = -1;
	    //order==0(NCHW), others(NHWC), order is set to zero by default.
	    //OpenCV use HWC as prefer.
	    int order = 1;
	    FaceRectwithFaceInfo[] results_rects =  ll.detectwithInfobyMetaData(encode2bytes(gray), gray.width(), gray.height(), 24, 1.2F, 3, 1);
        for(int i = 0; i < results_rects.length; i++){
            Imgproc.rectangle(img, new Rect(results_rects[i].x, results_rects[i].y,results_rects[i].width,results_rects[i].height), new Scalar(0,0,255));
            for(int j = 0; j < 5; j++){
                Imgproc.circle(img, new Point(results_rects[i].pts[j].x, results_rects[i].pts[j].y), 2, new Scalar(0,255,0));
            }
        }
	    if(show){
		    HighGui.imshow("test", img);
	        HighGui.waitKey();
	    }
        
		
		/*
		* Face Alignment
		*/
		byte[] aligned_faces_data = detector.alignFacebyMetaData(encode2bytes(gray), gray.width(), gray.height(), results_rects);
		Mat[] aligned_faces = encode2mats(aligned_face_data, results_rects.length);
		if(show && esults_rects.length > 0){
		    HighGui.imshow("aligned face", aligned_faces[0]);
	        HighGui.waitKey();
	    }
	}
	
	public static byte[] encode2bytes(Mat img){
        byte[] buffer = new byte[img.cols() * img.rows() * img.channels()];
        img.get(0,0, buffer);
        return buffer;
    }

	public static Mat[] encode2mats(byte[] metadata, int face_count){
        Mat[] faces = new Mat[face_count];
        if (metadata.length != face_count * 3 * 128 *128){
            return faces;
        }
        int n_offset = 3 * 128 *128;
        int c_offset = 128 * 128;
        for (int i = 0; i < face_count; i++){
            byte[] dst_data = new byte[3 *128 *128];
            faces[i] = new Mat(128, 128, CvType.CV_8UC3);
            for (int c = 0; c < 3; c++){
                for (int h = 0; h < 128; h++){
                    for (int w = 0; w < 128; w++){
                        dst_data[h * 3 * 128 + w * 3 + c]
                            = metadata[n_offset * i + c * c_offset + h * 128 + w];
                    }
                }
            }
            faces[i].put(0,0, dst_data);
        }
        return faces;
    }
}
```

##### Member Function`FaceRectwithFaceInfo[] detectwithInfobyMetaData(byte[] metadata, int width, int height, int minSize, float scale, int minNeighbors, int order);;`
Capability: detect and locate face in single-channel image

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|metadata|byte[]|user input|address of single-channel image data| image data should store continuously|
|width|int|user input|width of single-channel image| |
|height|int|user input|height of single-channel image| |
|minSize|int|effect value`>=24`|smallest detect window size|detected face area`>=minSize`|
|scale|float|`>1`|expand or shrink ratio of image|`>1.05`|
|minNeighbors|int|`>=0`|candidate boxes around face area|3 by default|
|order|int||array of face image data:NCHW/NHWC|order=0(NCHW),otherwise(NHWC)|

- Return Value
`FaceRectwithFaceInfo[]`Type, FaceRectwithFaceInfo contains information: detected face area, key points, head pose and possibility.

##### Member Function`byte[] alignFacebyMetaData(byte[] metadata, int width, int height, FaceRectwithFaceInfo[] face_info);`
Capability: Align Face

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|metadata|byte[]| |single-channel image used for detect face area| |
|height|`int`| |height of single-channel image| |
|width|`int`| |width of single-channel image| |
|face_info|FaceRectwithFaceInfo[]| |return value of *detectwithInfobyMetaData* method| |

- Return Value
`byte[]`, alignedFace data stored in vector stored in NCHW.


#### Longimila Performance
Test three face images(size: 640 \* 480,1280 \* 720,1920 \* 1080) on platform i7-8700K: loop 1000 times and calculate average detect time. 

##### Basic Information of Test Platform
Item | Description
:-:|:-:
Operating System | Windows 10 Enterprise 64bit |
Processor | Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz |
Core and Thread | 6 Cores and 12 Threads |
RAM | 32GB |
Compiler | MSVC 19.5 |
OpenMP | Yes |
SIMD Instruction Set | AVX2 |

##### Test Report

Parameter: minSize=48, scale=1.2, minNeighbors=3, useMultiThreads=false, doEarlyReject=false

Detect Time(ms)：

Image_Size | FRONTALVIEW | FRONTALVIEW_REINFORCE | MULTIVIEW | MULTIVIEW_REINFORCE
:-:|:-:|:-:|:-:|:-:
640 * 480 | 11.72 | 25.72 | 34.06 | 41.42 |
1280 * 720 | 26.14 | 45.44 | 69.09 | 85.07 |
1920 * 1080 | 76.59 | 122.38 | 155.89 | 186.86 |

![avatar](../640.jpg)
![avatar](../720.jpg)
![avatar](../1080.jpg)

Declaration: Test face images come from Internet, all rights belong to original Author. If we infringed your legal rights, please contact us to erase images. Thanks!