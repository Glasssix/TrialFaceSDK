#ifndef _BASE_SEARCH_HPP_
#define _BASE_SEARCH_HPP_
#include <iostream>
#include <vector>

namespace glasssix 
{
	namespace Irisvian 
	{

		class BaseSearch
		{
		public:
			BaseSearch() = default;

			BaseSearch(const std::vector<const float*> *baseData, int dimension) : baseData_(baseData), baseNum_((*baseData).size()) {}

			virtual ~BaseSearch() {}

			virtual void loadGraph(const char* graphPath) = 0;

			virtual void loadGraph(const char* graphPath, const char *basedataPath) = 0;

			virtual const std::vector<const float*>* getBasedata() = 0;

			virtual void optimizeGraph() = 0;

			virtual void searchVector(const std::vector<const float*>* queryData, unsigned topK,
				std::vector<std::vector<unsigned>> &returnIDs, std::vector<std::vector<float>> &returnSimilarities) = 0;

			virtual void saveResult(const char* resultPath, std::vector<std::vector<unsigned> > &returnIDs) = 0;

			unsigned navigateNode = 0;
			unsigned width = 0;
			bool isNormalized = false;
			std::vector<std::vector<unsigned > > ngraph;
			const std::vector<const float*>* baseData_;
			unsigned baseNum_;
		};
	}
}

#endif // !_BASE_SEARCH_HPP_