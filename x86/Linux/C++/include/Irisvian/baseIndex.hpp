#ifndef _BASE_INDEX_HPP_
#define _BASE_INDEX_HPP_
#include <iostream>
#include <vector>

namespace glasssix
{
	namespace Irisvian
	{
		class BaseIndex
		{
		public:

			BaseIndex() = default;

			BaseIndex(const std::vector<const float*> *baseData, int dimension) :baseData_(baseData), baseNum_((*baseData).size()) {}

			BaseIndex(int dimension) {}

			virtual ~BaseIndex() {}

			virtual int buildGraph() = 0;

			virtual int buildGraph(const std::vector<const float*> *baseData) = 0;

			virtual void saveGraph(const char *nGraphPath) = 0;

			virtual void saveGraph(const char *nGraphPath, const char *basedataPath) = 0;

			unsigned navigateNode = 0;
			unsigned width = 0;
			bool isNormalized = false;
			std::vector<std::vector<unsigned > > finalGraph;
			const std::vector<const float*> *baseData_;
			unsigned baseNum_;
			
		};
	}
}

#endif // !_BASE_INDEX_HPP_