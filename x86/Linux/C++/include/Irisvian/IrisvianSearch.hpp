#ifndef _IRISVIAN_SEARACH_HPP_
#define _IRISVIAN_SEARACH_HPP_

#include <iostream>
#include <vector>
#include <string>
#include "baseIndex.hpp"
#include "baseSearch.hpp"


#ifdef EXPORT_IRISVIAN
#undef EXPORT_IRISVIAN
#ifdef _MSC_VER
#define EXPORT_IRISVIAN __declspec(dllexport)
#else
#define EXPORT_IRISVIAN
#endif
#else
#ifdef _MSC_VER
#define EXPORT_IRISVIAN __declspec(dllimport)
#else
#define EXPORT_IRISVIAN
#endif
#endif

namespace glasssix
{
	namespace Irisvian
	{
		class EXPORT_IRISVIAN IrisvianSearch
		{
			IrisvianSearch() {}

			IrisvianSearch(const IrisvianSearch&){}

			IrisvianSearch& operator=(const IrisvianSearch&);

		public:

			IrisvianSearch(const std::vector<const float*> *baseData, int dimension);

			IrisvianSearch(int dimension);

			~IrisvianSearch();

			int buildGraph() const;

			int buildGraph(const std::vector<const float*> *baseData) const;

			void saveGraph(const char *graphPath) const;


			void saveGraph(std::string graphPath) const
			{
				saveGraph(graphPath.c_str());
			}


			void saveGraph(const char *graphPath, const char *basedataPath) const;


			void saveGraph(std::string graphPath, std::string basedataPath) const
			{
				saveGraph(graphPath.c_str(), basedataPath.c_str());
			}


			void loadGraph(const char* graphPath) const;


			void loadGraph(std::string graphPath) const
			{
				loadGraph(graphPath.c_str());
			}

			const std::vector<const float*>* getBasedata() const;

			void loadGraph(const char* graphPath, const char *basedataPath) const;

			void loadGraph(std::string graphPath, std::string basedataPath) const
			{
				loadGraph(graphPath.c_str(), basedataPath.c_str());
			}

			void optimizeGraph() const;

			void searchVector(const std::vector<const float*>* queryData, unsigned topK,
				std::vector<std::vector<unsigned>> &returnIDs, std::vector<std::vector<float>> &returnSimilarities) const;

			void saveResult(const char* resultPath, std::vector<std::vector<unsigned> > &returnIDs) const;

			void saveResult(std::string resultPath, std::vector<std::vector<unsigned> > &returnIDs) const
			{
				saveResult(resultPath.c_str(), returnIDs);
			}

			static std::string getVersion();

		private:
			BaseIndex *index_;
			BaseSearch *search_;
		};
	}
}

#endif // !_IRISVIAN_SEARACH_HPP_