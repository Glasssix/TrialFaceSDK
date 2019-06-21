#ifndef _ROMANCIADETECTOR_HPP_
#define _ROMANCIADETECTOR_HPP_

#include <vector>
#include <string>
#include <memory>
#include "BaseLonginusCascade.hpp"
#include "../Romancia/romancia.hpp"
#include "matcher.hpp"
#ifdef USE_OPENCV
#include <opencv2/opencv.hpp>
#endif
#ifdef TRIAL
#include "../Damocles/Damocles.hpp"
#endif // !TRIAL

namespace glasssix
{
	namespace longinus
	{
		typedef enum DetectionType
		{
			FRONTALVIEW,
			FRONTALVIEW_REINFORCE,
			MULTIVIEW,
			MULTIVIEW_REINFORCE
		}DetectionType;
		struct FaceRectwithFaceInfo : public FaceRect
		{
			Point2f pts[5];
			float yaw;
			float pitch;
			float roll;
			//float prob;

			FaceRectwithFaceInfo() {}
			FaceRectwithFaceInfo(const FaceRect& rect)
			{
				*dynamic_cast<FaceRect *>(this) = rect;
			}

			FaceRectwithFaceInfo &operator = (const FaceRect& rect)
			{
				*dynamic_cast<FaceRect *>(this) = rect;
				return *this;
			}
		};

#ifdef USE_OPENCV
		static std::vector<cv::Mat> encode2mats(std::vector<unsigned char> face_data, int face_count)
		{
			std::vector<cv::Mat> faces;
			assert(face_data.size() == face_count * 3 * 128 * 128);
			for (size_t i = 0; i < face_count; i++)
			{
				unsigned char* src_data = new unsigned char[3 * 128 * 128];
				memcpy(src_data, face_data.data() + i * 3 * 128 * 128, 3 * 128 * 128);
				cv::Mat dst = cv::Mat(128, 128, CV_8UC3);
				int src_offset = 128 * 128;
				int* c_src_offset = new int[3];
				for (int c = 0; c < 3; c++)
				{
					c_src_offset[c] = c * src_offset;
				}
				for (int h = 0; h < 128; h++)
				{
					unsigned char* dst_data = dst.ptr<unsigned char>(h);
					int src_sub_offset = h * 128;
					for (int w = 0; w < 128; w++)
					{
						for (int c = 0; c < 3; c++)
						{
							dst_data[w * 3 + c] = src_data[c_src_offset[c] + src_sub_offset + w];
						}
					}
				}
				delete c_src_offset;
				faces.push_back(dst);
				delete src_data;
			}
			return faces;
		}
#endif

		static void extract_faceinfo(std::vector<FaceRectwithFaceInfo> face_info, 
			std::vector<std::vector<int>>& bboxes, std::vector<std::vector<int>>& landmarks)
		{
			bboxes.clear();
			landmarks.clear();
			for (size_t i = 0; i < face_info.size(); i++)
			{
				bboxes.push_back({ face_info[i].x, face_info[i].y, face_info[i].width, face_info[i].height });
				landmarks.push_back({ static_cast<int>(face_info[i].pts[0].x), static_cast<int>(face_info[i].pts[0].y),
													  static_cast<int>(face_info[i].pts[1].x), static_cast<int>(face_info[i].pts[1].y),
													  static_cast<int>(face_info[i].pts[2].x), static_cast<int>(face_info[i].pts[2].y),
													  static_cast<int>(face_info[i].pts[3].x), static_cast<int>(face_info[i].pts[3].y),
													  static_cast<int>(face_info[i].pts[4].x), static_cast<int>(face_info[i].pts[4].y) });
			}
		}

		static void extract_biggest_faceinfo(std::vector<FaceRectwithFaceInfo> face_info,
			std::vector<std::vector<int>>& bboxes, std::vector<std::vector<int>>& landmarks)
		{
			bboxes.clear();
			landmarks.clear();
			int index = 0;
			float area = 0.0f;
			for (size_t i = 0; i < face_info.size(); i++)
			{
				if (face_info[i].width * face_info[i].height > area)
				{
					index = i;
					area = face_info[i].width * face_info[i].height;
				}
			}
			if (area <= 0.0f)
			{
				return;
			}
			bboxes.push_back({ face_info[index].x, face_info[index].y, face_info[index].width, face_info[index].height });
			landmarks.push_back({ static_cast<int>(face_info[index].pts[0].x), static_cast<int>(face_info[index].pts[0].y),
												  static_cast<int>(face_info[index].pts[1].x), static_cast<int>(face_info[index].pts[1].y),
												  static_cast<int>(face_info[index].pts[2].x), static_cast<int>(face_info[index].pts[2].y),
												  static_cast<int>(face_info[index].pts[3].x), static_cast<int>(face_info[index].pts[3].y),
												  static_cast<int>(face_info[index].pts[4].x), static_cast<int>(face_info[index].pts[4].y) });
		}

		class LonginusDetector
		{
		public:
			LonginusDetector(int device = -1);
			virtual ~LonginusDetector();
			std::vector<FaceRect> detect(unsigned char *gray, int width, int height, int step, int minSize, float scale,
				int minNeighbors, bool useMultiThreads = false, bool doEarlyReject = false);
			std::vector<FaceRectwithFaceInfo> detect(unsigned char *gray, int width, int height, int step, int minSize, float scale,
				int minNeighbors, int order = 0, bool useMultiThreads = false, bool doEarlyReject = false);

			std::vector<Match_Retval> match(std::vector<FaceRect> &faceRect, const int frame_extract_frequency) const;

			std::vector<Match_Retval> match(std::vector<FaceRectwithFaceInfo> &faceRect, const int frame_extract_frequency) const;

			std::vector<unsigned char> alignFace(const unsigned char* ori_image, int n, int channels, int height, int width, 
				std::vector<std::vector<int>> bbox, std::vector<std::vector<int> >landmarks) const;

#ifndef TRIAL
			std::vector<FaceRectwithFaceInfo> detectEx(const unsigned char* image, const int channels, const int height, const int width,
				const int minSize, const float* threshold, const float factor, const int stage) const;
#endif // !TRIAL

#ifndef RELEASE_SDK
			void load(std::vector<std::string> cascades, int device = -1);
#endif
			void set(DetectionType detectionType, int device = -1);

			static std::string getVersion();


		private:
			int device_;
			std::vector<std::shared_ptr<BaseLonginusCascade>> *cascades_;
			std::unique_ptr<vBanshee> bansheelia_;
			std::vector<unsigned char> data_;
			std::unique_ptr<Matcher> matcher_;

#ifdef TRIAL
			std::unique_ptr<vDamocles> diodorus_;
#endif // !TRIAL

		};
	}
}

#endif// !_ROMANCIADETECTOR_HPP_
