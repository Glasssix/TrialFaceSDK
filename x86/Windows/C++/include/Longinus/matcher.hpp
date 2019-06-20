#ifndef _MATCHER_HPP_
#define _MATCHER_HPP_
#include <string>
#include <vector>
#include <map>

#include "match_recter.hpp"

namespace glasssix
{
	namespace longinus
	{
		class Matcher
		{
			std::map<std::string, Map_Val> matcher_map;
			int num_face_rect = 0;
			int index = 0;
		public:
			Matcher();
			~Matcher();

			std::vector<Match_Retval> match(std::vector<FaceRect> &faceRect,
				const int frame_extract_frequency);

		};
	}
} // end-namespace

#endif //!_MATCHER_HPP_