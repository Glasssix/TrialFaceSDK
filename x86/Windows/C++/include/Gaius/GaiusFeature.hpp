#ifndef _GAIUS_FEATURE_HPP_
#define _GAIUS_FEATURE_HPP_


#ifdef EXPORT_GAIUS
#undef EXPORT_GAIUS
#ifdef _MSC_VER // For Windows
#ifdef _WINDLL // Dynamic lib
#define EXPORT_GAIUS __declspec(dllexport)
#else // Static lib
#define EXPORT_GAIUS
#endif // !_WINDLL
#elif defined(__linux__) // For Linux
#define EXPORT_GAIUS
#endif
#else
#ifdef _MSC_VER
#define EXPORT_GAIUS __declspec(dllimport)
#elif defined(__linux__)
#define EXPORT_GAIUS
#endif
#endif

#include "vunicorn_mobile.hpp"
#include <string>

namespace glasssix
{
	namespace gaius
	{
		class EXPORT_GAIUS GaiusFeature
		{
		public:

			GaiusFeature() {}

			GaiusFeature(int device);

			~GaiusFeature();

			std::vector<std::vector<float> > Forward(const unsigned char* input_data, unsigned num, int order = 0) const;

			static std::string getVersion();

		private:

			vUnicornMobile* mobile_unicornia_;

			std::vector<std::vector<float> > Forward(const float* input_data, unsigned num, int order = 0) const;
		};
	}
}

#endif // !_GAIUS_FEATURE_HPP_