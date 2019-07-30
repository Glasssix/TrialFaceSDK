#ifndef _IRISVIEL_SEARCH_HPP_
#define _IRISVIEL_SEARCH_HPP_

#include <iostream>
#include <vector>
#include <string>
#include "baseIndex.hpp"
#include "baseSearch.hpp"

#ifdef EXPORT_IRISVIEL
#undef EXPORT_IRISVIEL
#ifdef _MSC_VER // For Windows
#ifdef _WINDLL // Dynamic lib
#define EXPORT_IRISVIEL __declspec(dllexport)
#else // Static lib
#define EXPORT_IRISVIEL
#endif // !_WINDLL
#elif defined(__linux__) // For Linux
#define EXPORT_IRISVIEL
#endif
#else
#ifdef _MSC_VER
#define EXPORT_IRISVIEL __declspec(dllimport)
#elif defined(__linux__)
#define EXPORT_IRISVIEL
#endif
#endif

namespace glasssix
{
	namespace irisviel
	{
		class EXPORT_IRISVIEL IrisvielSearch
		{

			IrisvielSearch(const IrisvielSearch&){}

			IrisvielSearch& operator=(const IrisvielSearch&);

		public:
            IrisvielSearch() = delete;

			IrisvielSearch(const std::vector<const float*> *baseData, int dimension);

			IrisvielSearch(int dimension);

			virtual ~IrisvielSearch();

			int buildGraph() const;

			int buildGraph(const std::vector<const float*> *baseData) const;

			void saveGraph(const char *graphPath) const;


			void saveGraph(std::string graphPath) const;


			void saveGraph(const char *graphPath, const char *basedataPath) const;


			void saveGraph(std::string graphPath, std::string basedataPath) const;


			void loadGraph(const char* graphPath) const;


			void loadGraph(std::string graphPath) const;

			const std::vector<const float*>* getBasedata() const;

			void loadGraph(const char* graphPath, const char *basedataPath) const;

			void loadGraph(std::string graphPath, std::string basedataPath) const;

			void optimizeGraph() const;

			void searchVector(const std::vector<const float*>* queryData, unsigned topK,
				std::vector<std::vector<unsigned>> &returnIDs, std::vector<std::vector<float>> &returnSimilarities) const;

			void saveResult(const char* resultPath, std::vector<std::vector<unsigned> > &returnIDs) const;

			void saveResult(std::string resultPath, std::vector<std::vector<unsigned>>& returnIDs) const;

			static std::string getVersion();

		private:
			BaseIndex *index_;
			BaseSearch *search_;
		};
	}
}

#endif // !_IRISVIEL_SEARCH_HPP_