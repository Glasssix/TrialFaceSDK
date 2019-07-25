

## Face Detect V1.0(TrialFaceSDK)
### Capability Introduction
#### Interface Capability
- **Face Detect**: Detect face in images, and calculate possibility, angle, position of key points(eyes, nose, mouth)
#### Dependencies
- **CPU**: MSVCP140、VCRUNTIME140
### Invoke Method
#### Example Code 1
```c++
#include <opencv2/opencv.hpp>
#include "Longinus/LonginusDetector.hpp"

using namespace glasssix;
using namespace glasssix::longinus;

int main()
{
    //do not support GPU in TrialFaceSDK
	int device = -1;//using CPU when device is less than zero, otherwise use the GPU numbered by 'device', device is set to -1 by default.
	LonginusDetector detector;
	detector.set(FRONTALVIEW, device);
	
	cv::Mat img = cv::imread("../img/exciting.png");
	cv::Mat gray;
	cv::cvtColor(img, gray, CV_BGR2GRAY);
	std::vector<FaceRect> rects = detector.detect(gray.data, gray.cols, gray.rows, gray.step[0], 24, 1.1f, 3, false, false);
	for (int i = 0; i < rects.size(); i++)
		cv::rectangle(img, cv::Rect(rects[i].x, rects[i].y, rects[i].width, rects[i].height), cv::Scalar(0, 255, 0));

	cv::imshow("hehe", img);
	cv::waitKey(0);
	return 0;
}
```
#### Class Description: LonginusDetector
##### Member Function`void set(DetectionType detectionType, int device);`
Capability: set detect method and device

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|detectionType|enum DetectionType|FRONTALVIEW<br>FRONTALVIEW_REINFORCE<br>MULTIVIEW<br> MULTIVIEW_REINFORCE||detect effect and time consuming both ascend|
|device|int|`<0`<br>`>=0`|use cpu<br>use gpu numberd by 'device'| |


##### Member Function`std::vector<FaceRect> detect(unsigned char *gray, int width, int height, int step, int minSize, float scale, int min_neighbors, bool useMultiThreads = false, bool doEarlyReject = false);`
Capability: detect and locate face in single-channel image

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|gray|`unsigned char *`|user input|address of single-channel image data| image data should store continuously|
|width|int|user input|width of single-channel image| |
|height|int|user input|height of single-channel image| |
|step|int|user input|bytes of each row in single-channel image| |
|minSize|int|effect value`>=24`|smallest detect window size|detected face area`>=minSize`|
|scale|float|`>1`|expand or shrink ratio of image|`>1.1`|
|min_neighbors|int|`>=0`|candidate boxes around face area|3 by default|
|useMultiThreads|bool|true<br>false|use multi-thread<br>use single-thread|take effect when using cpu, false by default|
|doEarlyReject|bool|true<br>false|adopt early reject<br>don't adopt|detect speed promote, with detect effect descend, false by default|

- Return Value
`std::vector<FaceRect>`, FaceRect contains detected face area information

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
```c++
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Longinus/LonginusDetector.hpp"

using namespace cv;
using namespace glasssix::longinus;
using namespace std;

int main()
{
	//transform color image to gray image
	Mat src_image, gray_image;
	src_image = imread("../img/exciting.png");
	cvtColor(src_image, gray_image, CV_BGR2GRAY);

	//detect face rect
	LonginusDetector detector;
	//do not support GPU in TrialFaceSDK
	int device = -1;//using CPU when device is less than zero, otherwise use the GPU numbered by 'device', device is set to -1 by default.
	int order = 0;//order==0(NCHW),others(NHWC), order is set to zero by default.
	detector.set(MULTIVIEW_REINFORCE, -1);	
	std::vector<FaceRectwithFaceInfo> faceBox;
	
    //detect from gray image, recommended!
	faceBox = detector.detect(gray_image.data, gray_image.cols, gray_image.rows, gray_image.step[0], 80, 1.1f, 3, order, false, false);

	//store bboxes with face rects , store landmarks with key points(eye,nose,mouth)
	std::vector<std::vector<int>> bboxes;
	std::vector<std::vector<int>> landmarks;
	extract_faceinfo(faceBox, bboxes, landmarks);
	
	std::vector<std::vector<float>> angles;
	angles.resize(faceBox.size());
	//draw face rects and key points on src_image
	for (size_t i = 0; i < faceBox.size(); i++)
	{
		//head pose
		angles[i].push_back(faceBox[i].yaw);
		angles[i].push_back(faceBox[i].pitch);
		angles[i].push_back(faceBox[i].roll);

		//draw face rects
		cv::rectangle(src_image, cv::Rect(bboxes[i][0], bboxes[i][1], bboxes[i][2], bboxes[i][3]), cv::Scalar(255, 0, 0), 1);
		
		//draw key points
		cv::circle(src_image, cv::Point(landmarks[i][0], landmarks[i][1]), 3, Scalar(0, 255, 0), -1);//left eye
		cv::circle(src_image, cv::Point(landmarks[i][2], landmarks[i][3]), 3, Scalar(0, 255, 0), -1);//right eye
		cv::circle(src_image, cv::Point(landmarks[i][4], landmarks[i][5]), 3, Scalar(0, 255, 0), -1);//nose
		cv::circle(src_image, cv::Point(landmarks[i][6], landmarks[i][7]), 3, Scalar(0, 255, 0), -1);//left mouse
		cv::circle(src_image, cv::Point(landmarks[i][8], landmarks[i][9]), 3, Scalar(0, 255, 0), -1);//right mouse
	}

	//show image labeled with face rects and key points
	imshow("src", src_image);
	waitKey(0);
	
	//face alignment
	std::vector<unsigned char> alignedImages = detector.alignFace(gray_image.data, 1, gray_image.channels(), gray_image.rows, gray_image.cols, bboxes, landmarks);
	unsigned char* temp = (unsigned char*)malloc(3 * 128 * 128);
	for (size_t i = 0; i < faceBox.size(); i++)
	{
		memcpy(temp, alignedImages.data() + i * 3 * 128 * 128, 3 * 128 * 128 * sizeof(unsigned char));
		cv::Mat alignedFace(128,128,CV_8UC3,temp);
		cv::imshow("alignedFace", alignedFace);
		cv::waitKey(0);
	}
	delete temp;
	
	destroyAllWindows();
	return 0;
}
```

##### Member Function`std::vector<FaceRectwithFaceInfo> detect(unsigned char *gray, int width, int height, int step, int minSize, float scale, int min_neighbors, int order = 0, bool useMultiThreads = false, bool doEarlyReject = false);`
Capability: detect and locate face in single-channel image

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|gray|`unsigned char *`|user input|address of single-channel image data| image data should store continuously|
|width|int|user input|width of single-channel image| |
|height|int|user input|height of single-channel image| |
|step|int|user input|bytes of each row in single-channel image| |
|minSize|int|effect value`>=24`|smallest detect window size|detected face area`>=minSize`|
|scale|float|`>1`|expand or shrink ratio of image|`>1.1`|
|min_neighbors|int|`>=0`|candidate boxes around face area|3 by default|
|order|int||array of face image data:NCHW/NHWC|order=0(NCHW),otherwise(NHWC)|
|useMultiThreads|bool|true<br>false|use multi-thread<br>use single-thread|take effect when using cpu, false by default|
|doErlyReject|bool|true<br>false|adopt early reject<br>don't adopt|detect speed promote, with detect effect descend, false by default|

- Return Value
`std::vector<FaceRectwithFaceInfo>`Type, FaceRectwithFaceInfo contains information: detected face area, key points, possibility

##### Member Function`void extract_faceinfo(std::vector<FaceRectwithFaceInfo> face_info, std::vector<std::vector<int>>& bboxes, std::vector<std::vector<int>>& landmarks);`
Capability: extract face area to save in bboxes, and extract key points to save in landmarks

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|face_info|`std::vector<FaceRectwithFaceInfo>`| |detected face information| |
|bboxes|`std::vector<std::vector<int>>`| |bboxes.size(): number of faces detected, bboxes[i][0]:x，bboxes[i][1]:y，bboxes[i][2]:width，bboxes[i][3]:height| |
|landmarks|`std::vector<std::vector<int>>`| |landmarks.size():number of faces detected, landmarks[i][0]:x_lefteye，landmarks[i][1]:y_lefteye，landmarks[i][2]:x_righteye，landmarks[i][3]:y_righteye，landmarks[i][4]:x_nose，landmarks[i][5]:y_nose，landmarks[i][6]:x_leftmouse，landmarks[i][7]:y_leftnouse，landmarks[i][8]:x_rightmouth，landmarks[i][9]:y_rightmouth| |

##### Member Function`void extract_biggest_faceinfo(std::vector<FaceRectwithFaceInfo> face_info, std::vector<std::vector<int>>& bboxes, std::vector<std::vector<int>>& landmarks);`
Capability: extract biggest face area to save in bboxes, and extract key points of biggest face area to save in landmarks

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|face_info|`std::vector<FaceRectwithFaceInfo>`| |detected face information| |
|bboxes|std::vector<std::vector<int>>| |bboxes.size(): number of faces detected, bboxes[i][0]:x，bboxes[i][1]:y，bboxes[i][2]:width，bboxes[i][3]:height| |
|landmarks|std::vector<std::vector<int>>| |landmarks.size():number of faces detected, landmarks[i][0]:x_lefteye，landmarks[i][1]:y_lefteye，landmarks[i][2]:x_righteye，landmarks[i][3]:y_righteye，landmarks[i][4]:x_nose，landmarks[i][5]:y_nose，landmarks[i][6]:x_leftmouse，landmarks[i][7]:y_leftnouse，landmarks[i][8]:x_rightmouth，landmarks[i][9]:y_rightmouth| |

##### Member Function`std::vector<unsigned char> alignFace(const unsigned char* ori_image, int n, int channels, int height, int width, std::vector<std::vector<int>> bbox, std::vector<std::vector<int> >landmarks);`
Capability: Align Face

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|ori_image|`const unsigned char*`| |single-channel image used for detect face area| |
|n|`int`| |number of single-channel image| |
|channels|`int`| |channel of single-channel image| |
|height|`int`| |height of single-channel image| |
|width|`int`| |width of single-channel image| |
|bbox|`std::vector<std::vector<int>>`| |bboxes.size(): number of faces detected, bboxes[i][0]:x，bboxes[i][1]:y，bboxes[i][2]:width，bboxes[i][3]:height| |
|landmarks|`std::vector<std::vector<int>>`| |landmarks.size():number of faces detected, landmarks[i][0]:x_lefteye，landmarks[i][1]:y_lefteye，landmarks[i][2]:x_righteye，landmarks[i][3]:y_righteye，landmarks[i][4]:x_nose，landmarks[i][5]:y_nose，landmarks[i][6]:x_leftmouse，landmarks[i][7]:y_leftnouse，landmarks[i][8]:x_rightmouth，landmarks[i][9]:y_rightmouth| |

- Return Value
`std::vector<unsigned char>`, alignedFace data stored in vector


## Face Match
### Capability Introduction
#### Interface Capability
- **Face Match**: input detect result of consecutive video frame, then judge whether faces belong to a same person. Take effect when camera position is fixed.
### Invoke Method
#### Example Code 3:
```c++
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Longinus/LonginusDetector.hpp"
#include <map>

using namespace glasssix;
using namespace glasssix::longinus;

int main(int argc, char** argv)
{
	cv::Mat frame;
	cv::Mat gray;
	int frame_extract_frequency = 5; // frequency of extracting one frame
	cv::VideoCapture capture("..\\data\\group.mp4");

	if (!capture.isOpened())
	{
		std::cout << "Reading Video Failed !" << std::endl;
		getchar();
		return 0;
	}

	int frame_num = capture.get(cv::CAP_PROP_FRAME_COUNT);
	int device = -1;
	LonginusDetector detector;
	detector.set(MULTIVIEW_REINFORCE, device);

	// loop through every frame in the video
	for (int i = 0; i < frame_num - 1; i++)
	{
		capture >> frame;
		cv::cvtColor(frame, gray, cv::COLOR_RGB2GRAY);

		if (i % frame_extract_frequency == 0)
		{
			// retrieve a number of rects, it calls detector.detect(), which returns frontal face detections.
	        std::vector<FaceRect> rects = detector.detect(gray.data, gray.cols, gray.rows, gray.step[0], 24, 1.1f, 3, false, false);
			auto results = detector.match(rects, frame_extract_frequency);// you can also use std::vector<FaceRectwithFaceInfo>, modify detector.detect()

			// show the face rects and string id on every frame
			for (size_t j = 0; j < results.size(); j++) {
				cv::Rect temp_(results[j].rect.x, results[j].rect.y, results[j].rect.width, results[j].rect.height);
				cv::rectangle(frame, temp_, cv::Scalar(0, 0, 255));
				cv::putText(frame, results[j].id, temp_.tl(), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1, CV_AA);
			} // end-for-j
			
			//matcher_.print_map();
		} // end-if-mod-frequency
		
		// display 1 frame every num frames
		if (i % frame_extract_frequency == 0) {
			cv::imshow("test", frame);
			cv::waitKey(5);
		}
	} // end-for-i

	return 0;
}
```
#### Class Description: Matcher
##### Member Function`std::vector<Match_Retval> match(std::vector<FaceRect> &faceRect, const int frame_extract_frequency);`
Capability: set an uuid for each input face area, judge whether it's new in video frames.

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|faceRect|`std::vector<FaceRect>`|--|get by function LonginusDetector.detect()|
|frame_extract_frequency|int|positive integer|interval between two frames to be dealt with| |

- Return Value
`std::vector<Match_Retval>`Type, Match_Retval contains detected face area information and uuid

##### Member Function`std::vector<Match_Retval> match(std::vector<FaceRectwithFaceInfo> &faceRect, const int frame_extract_frequency);`
Capability: set an uuid for each input face area, judge whether it's new in video frames.

|Parameter|Parameter Type|Value|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|faceRect|`std::vector<FaceRectwithFaceInfo>`|--|get by function LonginusDetector.detect()|
|frame_extract_frequency|int|positive integer|interval between two frames to be dealt with| |

- Return Value
`std::vector<Match_Retval>`Type, Match_Retval contains detected face area information and uuid

###### Struct Description: Match_Retval

|Member Variable|Type|Illustration|Remark|
|:--------:|:--------:|:--------:|:--------:|
|rect|FaceRect|face area| |
|id|std::string|32bit uuid| |
|is_new|bool|flag to judge whether this face area belongs to a new person| |


#### Longinus Performance
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