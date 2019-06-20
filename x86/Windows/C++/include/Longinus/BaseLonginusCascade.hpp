#ifndef BASELONGINUS_HPP
#define BASELONGINUS_HPP
#include <vector>
#include "common.hpp"

namespace glasssix
{
	namespace longinus
	{
		typedef enum LonginusCascadeType
		{
			FRONTAL,
			FRONTAL_REINFORCE,
			LEFT_PROFILE,
			LEFT_PROFILE_REINFORCE,
			RIGHT_PROFILE,
			RIGHT_PROFILE_REINFORCE
		}LonginusCascadeType;

		class BaseLonginusCascade
		{
		public:
			virtual ~BaseLonginusCascade() {}
			virtual void LoadCascade(LonginusCascadeType cascadeType, int device = -1) = 0;
			virtual int getWinWidth() const = 0;
			virtual int getWinHeight() const = 0;
			virtual bool isEmpty() = 0;
		};
	}
}

#endif

