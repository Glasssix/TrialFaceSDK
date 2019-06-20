#pragma once
#ifndef _VUNICORN_MOBILE_HPP_
#define _VUNICORN_MOBILE_HPP_
#include <vector>

namespace glasssix
{
	namespace gaius
	{
		class vUnicornMobile
		{
		public:

			vUnicornMobile() {}

			vUnicornMobile(int device) {}

			virtual ~vUnicornMobile() {}

			virtual std::vector<std::vector<float> > Forward(const float* input_data, unsigned num, int order) = 0;

			virtual std::vector<std::vector<float> > Forward(const unsigned char* input_data, unsigned num, int order) = 0;

		};
	}
}

#endif // !_VUNICORN_MOBILE_HPP_