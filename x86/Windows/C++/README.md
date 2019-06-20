# Glasssix TrialFaceSDK
Document, binary module, example and billboard for face SDK of internal version


#### Example Code：Whole Process: Face Detect, Face Alignment, Extract Feature, Face Search
```c++

#include <iostream>
#include "Longinus/LonginusDetector.hpp"
#include "Gaius/GaiusFeature.hpp"
#include "Irisvian/IrisvianSearch.hpp"
#include <opencv2/opencv.hpp>

using namespace glasssix;
using namespace glasssix::gaius;
using namespace glasssix::Irisvian;

void static loadData(const char* filename, std::vector<const float*> &data, unsigned numItem, unsigned dim)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (!in.is_open())
	{
		std::cout << "open file error" << std::endl; exit(-1);
	}
	in.seekg(0, std::ios::beg);
	for (int i = 0; i < numItem; ++i)
	{
		float *temp_data = (float*)malloc(dim * sizeof(float));
		in.read((char*)(temp_data), dim * sizeof(float));
		data.push_back(const_cast<const float*>(temp_data));
	}
	in.close();
}

std::vector<std::vector<float> > detect_align_extract(cv::Mat img, unsigned char* data, int device, int order)
{
	int channel = img.channels();
	int height = img.rows;
	int width = img.cols;

	glasssix::longinus::LonginusDetector detector;
	detector.set(longinus::MULTIVIEW_REINFORCE, device);
	glasssix::gaius::GaiusFeature feat_extractor128(device);

	std::vector<longinus::FaceRectwithFaceInfo> face_info;
	std::vector<std::vector<int>> bboxes;
	std::vector<std::vector<int>> landmarks;
	std::vector<unsigned char> alignedfaces_data;
	std::vector<std::vector<float> > features128;

	face_info = detector.detect(data, width, height, width, 24, 1.1f, 3, order);//data has single channel, so order can be 0 or 1

	if (face_info.size() <= 0)
	{
		return std::vector<std::vector<float> >();
	}

	// alignment step
	longinus::extract_faceinfo(face_info, bboxes, landmarks);
	//alignedfaces_data memory array as NCHW:(face_info.size(),3,128,128)
	alignedfaces_data = detector.alignFace(data, face_info.size(), 1, height, width, bboxes, landmarks);

	for (int i = 0; i < bboxes.size(); i++)
	{
		std::cout << "bbox:" << bboxes[i][0] << " " << bboxes[i][1] << " " << bboxes[i][2] << " " << bboxes[i][3] << std::endl;
		std::cout << "landmarks:" << landmarks[i][0] << " " << landmarks[i][1] << " " << landmarks[i][2] << " " << landmarks[i][3] << " " << landmarks[i][4] << " "
			<< landmarks[i][5] << " " << landmarks[i][6] << " " << landmarks[i][7] << " " << landmarks[i][8] << " " << landmarks[i][9] << std::endl;
	}

	// feature extraction step
	features128 = feat_extractor128.Forward(alignedfaces_data.data(), face_info.size(), 0);

	return features128;
}

std::vector<std::vector<float>> face_search(std::vector<std::vector<float>> features)
{
	std::vector<const float*> baseData;
	std::vector<const float*> queryData;
	std::string baseDataPath = "./map512.bin";

	for (int i = 0; i < features.size(); i++)
	{
		queryData.push_back(features[i].data());
	}

	unsigned baseNum = 10000;
	unsigned queryNum = features.size();
	unsigned dimension = features[0].size();
	loadData(baseDataPath.c_str(), baseData, baseNum, dimension);

	IrisvianSearch oIndex(&baseData, dimension);
	oIndex.buildGraph();
	oIndex.optimizeGraph();

	unsigned topK = 1;
	std::vector<std::vector<unsigned>> IDs;
	std::vector<std::vector<float>> similarities;

	oIndex.searchVector(&queryData, topK, IDs, similarities);
	return similarities;
}

int main()
{
	cv::Mat img = cv::imread("D:/lfw/Ben_Chandler/Ben_Chandler_0001.jpg");
	cv::Mat gray;
	cv::cvtColor(img, gray, CV_BGR2GRAY);
	unsigned char* data = gray.data;
	int device = -1;//CPU
	int order = 0;//NCHW

	//face features extracted
	std::vector<std::vector<float>> features = detect_align_extract(img, data, device, order);

	//search with baseData
	std::vector<std::vector<float>> returnSimilarities = face_search(features);

	//judge with threshold value 0.5
	for (int i = 0; i < returnSimilarities.size(); i++)
	{
		std::cout << "similarity:" << returnSimilarities[i][0] << ", ";
		if (returnSimilarities[i][0] > 0.5)
		{
			std::cout << "pass!" << std::endl;
		}
		else
		{
			std::cout << "deny!" << std::endl;
		}
	}

	return 0;
}
```