#ifndef _DAMOCLES_HPP_
#define _DAMOCLES_HPP_

#include "vdamocles.hpp"

namespace glasssix
{
	namespace longinus
	{
		class Damocles
		{
		public:

			Damocles() {}

			Damocles(int device);

			~Damocles();

			std::vector<FaceInfomation> Detect(const unsigned char* img, const int channels, const int height, const int width,
				const int min_size, const float* threshold, const float factor, const int stage, int order) const;

		private:
			vDamocles *diodorus_;
		};
	}
}

#endif // !_DAMOCLES_HPP_