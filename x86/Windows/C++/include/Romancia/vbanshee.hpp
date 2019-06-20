#ifndef _VBANSHEE_HPP_
#define _VBANSHEE_HPP_
#include <vector>

namespace glasssix
{
	namespace longinus
	{
		class vBanshee
		{
		public:

			vBanshee() {}

			vBanshee(int device) {}

			virtual ~vBanshee() {}

			virtual void Forward(const float* input_data, unsigned num, int order) = 0;

			virtual void Forward(const unsigned char* input_data, unsigned num, int order) = 0;

			virtual void getParam(std::vector<std::vector<float> > &keypointParam, unsigned num) = 0;

			virtual std::vector<unsigned char> alignFace(const unsigned char* ori_image, int n, int channels, int height, int width, std::vector<std::vector<int>> bbox, std::vector<std::vector<int> >landmarks) = 0;

		};
	}
}

#endif // !_VBANSHEE_HPP_