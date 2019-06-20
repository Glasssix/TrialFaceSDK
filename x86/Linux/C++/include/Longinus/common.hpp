#ifndef COMMON_HPP
#define COMMON_HPP

#include <vector>
#include <string>
#include <memory> 

#ifdef EXPORT_LONGINUS
#undef EXPORT_LONGINUS
#ifdef _MSC_VER // For Windows
#ifdef _WINDLL // Dynamic lib
#define EXPORT_LONGINUS __declspec(dllexport)
#else // Static lib
#define EXPORT_LONGINUS
#endif //!_WINDLL
#elif defined(__linux__) // For Linux
#define EXPORT_LONGINUS 
#endif
#else  
#ifdef _MSC_VER
#define EXPORT_LONGINUS __declspec(dllimport)
#elif defined(__linux__)
#define EXPORT_LONGINUS 
#endif
#endif

namespace glasssix
{
	namespace longinus
	{
		typedef struct FaceRect {
			int x;
			int y;
			int width;
			int height;
			int neighbors;
			double confidence;

			FaceRect() :x(0), y(0), width(0), height(0), neighbors(0), confidence(0.0) {}
			FaceRect(int x_, int y_, int width_, int height_, int neighbors_, double confidence_)
				:x(x_), y(y_), width(width_), height(height_), neighbors(neighbors_), confidence(confidence_) {}
		} FaceRect;

		class BaseLonginusCascade;
		class EXPORT_LONGINUS LonginusDetector;

		typedef struct CandidateRect : public FaceRect
		{
			int index_in_image_pyramids;
			int ix;
			int iy;
			int xstep;
			int ystep;
			int xmax;
			int ymax;
			std::shared_ptr<BaseLonginusCascade> cascade;
			CandidateRect() :index_in_image_pyramids(-1), ix(-1), iy(-1), xstep(0), ystep(0), xmax(-1), ymax(-1), cascade(nullptr) {}
			CandidateRect(int x_, int y_, int width_, int height_, int neighbors_, double confidence_, 
				int index_in_image_pyramids_, int ix_, int iy_, int xstep_, int ystep_, int xmax_, int ymax_, std::shared_ptr<BaseLonginusCascade> cascade_)
			:FaceRect(x_, y_, width_, height_, neighbors_, confidence_), index_in_image_pyramids(-1), ix(-1), iy(-1), xstep(0), ystep(0), xmax(-1), ymax(-1), cascade(cascade_) {}
		}CandidateRect;

		void GroupRects(std::vector<FaceRect> &pFaces, int min_neighbors);

		typedef struct Point2i
		{
			int x;
			int y;
			Point2i() :x(-1), y(-1){}
			Point2i(int ix, int iy) :x(ix), y(iy) {}
		}Point;

		typedef struct Point2f
		{
			float x;
			float y;
			Point2f() :x(-1), y(-1) {}
			Point2f(float ix, float iy) :x(ix), y(iy) {}
		}Point2f;

		typedef struct ScaledMatrix
		{
			int factor1024x;
			int winStep;
			ScaledMatrix() :factor1024x(0), winStep(0) {}
			ScaledMatrix(int factor1024x_, int winStep_) :
				factor1024x(factor1024x_), winStep(winStep_){}
		}ScaledMatrix;

		typedef struct FaceBox {
			float xmin;
			float ymin;
			float xmax;
			float ymax;
			float score;
		} FaceBox;

		typedef struct FaceInfomation {
			float bbox_reg[4];
			float landmark[10];
			FaceBox bbox;
		} FaceInfomation;
	}
}

#endif