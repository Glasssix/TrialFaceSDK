## Face Search V1.0(TrialFaceSDK)
### Capability Introduction
#### Interface Capability
- **Face Search**: Search a given face from image library, return topK most similar faces.
#### Dependencied
- **CPU**: MSVCP140、VCRUNTIME140
### Use Cases
1. Size of image library equals 1.
   invoke function searchVector() directly.

2. Size of image library is larger than 1. Build ngraph, then search. Drop ngraph when program exit.

    buildGraph()->optimizeGraph()->searchVector()

3. Size of image library is larger than 1. Build and save ngraph, then search.

    buildGraph()->saveGraph()->optimizeGraph()->searchVector()

4. Size of image library is larger than 1. Load ngraph from disk, then search. Image library should remain the same when ngraph was generated.

    loadGraph()->optimizeGraph()->searchVector()

### Invoke Method
#### Example Code 1st: Size of image library equals 1. Invoke function searchVector() directly to accomplish face verification(1:1) task.
```c++
#include "Irisviel/IrisvielSearch.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace glasssix::irisviel;

//fill baseData and queryData from files
void static loadData(const char* filename, std::vector<const float*> &baseData, unsigned baseNumItem,
	std::vector<const float*> &queryData, unsigned queryNumItem, unsigned dim) {
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (!in.is_open()) { std::cout << "open file error" << std::endl; exit(-1); }
	in.seekg(0, std::ios::beg);
	for (int i = 0; i < baseNumItem; ++i)
	{
		float *temp_data = (float*)malloc(dim * sizeof(float));
		in.read((char*)(temp_data), dim * sizeof(float));
		baseData.push_back(const_cast<const float*>(temp_data));
	}
	for (int i = 0; i < queryNumItem; ++i)
	{
		float *temp_data = (float*)malloc(dim * sizeof(float));
		in.read((char*)(temp_data), dim * sizeof(float));
		queryData.push_back(const_cast<const float*>(temp_data));
	}
	in.close();
}

int main(int argc, char *argv[])
{
    vector<const float*> baseData;
    vector<const float*> queryData;
    unsigned baseNum = 1;
    unsigned queryNum = 1;
    unsigned dimension = 512;
	string resultPath = "./result_" + to_string(dimension) + "_" + to_string(baseNum) + ".bin";
    string sourceDataPath = "./map512.bin";
	
    //fill baseData and queryData
    loadData(sourceDataPath.c_str(), baseData, baseNum, queryData, queryNum, dimension);
    
    unsigned topK = 1;//topK cannot exceed the total number in baseData
    std::vector<std::vector<unsigned>> returnIDs;//face IDs returned，returnIDs.size() = queryNum, returnIDs[i].size()=topK
    std::vector<std::vector<float>> returnDistancesInPercentage;//similarity,returnDistancesInPercentage.size()=queryNum,returnDistancesInPercentage[i].size()=topK
    
	IrisvielSearch oSearch(&baseData, dimension);
    oSearch.searchVector(&queryData, topK, returnIDs, returnDistancesInPercentage);
    oSearch.saveResult(resultPath, returnIDs);//only face IDs are saved, similarity ignored 
    
    return 0;
}
```

#### Example Code 2nd：Size of image library is larger than 1. Build ngraph, then search. Drop ngraph when program exit.
```c++
#include "Irisviel/IrisvielSearch.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace glasssix::irisviel;

//fill baseData and queryData from files, erase function body for simplicity
void static loadData(const char* filename, std::vector<const float*> &baseData, unsigned baseNumItem,
	std::vector<const float*> &queryData, unsigned queryNumItem, unsigned dim) {}
	
int main(int argc, char *argv[])
{
    vector<const float*> baseData;
    vector<const float*> queryData;
    unsigned baseNum = 100000;
    unsigned queryNum = 1000;
    unsigned dimension = 512;
	string resultPath = "./result_" + to_string(dimension) + "_" + to_string(baseNum) + ".bin";
    string sourceDataPath = "./map512.bin";
	
    //fill baseData and queryData
    loadData(sourceDataPath.c_str(), baseData, baseNum, queryData, queryNum, dimension);
    
	//construct with both baseData and dimension
    IrisvielSearch oSearch(&baseData, dimension);
	oSearch.buildGraph();
	
	////also we can construct with dimension, then import baseData when buildGraph()
	//IrisvielSearch oSearch(dimension);
	//oSearch.buildGraph(&baseData);
	
    unsigned topK = 10;//topK cannot exceed the total number in baseData
    std::vector<std::vector<unsigned>> returnIDs;//face IDs returned，returnIDs.size() = queryNum, returnIDs[i].size()=topK
    std::vector<std::vector<float>> returnDistancesInPercentage;//similarity,returnDistancesInPercentage.size()=queryNum,returnDistancesInPercentage[i].size()=topK
    
	oSearch.optimizeGraph();
    oSearch.searchVector(&queryData, topK, returnIDs, returnDistancesInPercentage);
    oSearch.saveResult(resultPath, returnIDs);//only face IDs are saved, similarity ignored
    
    return 0;
}
```

#### Example Code 3rd: Size of image library is larger than 1. Build and save ngraph, then search.
```c++
#include "Irisviel/IrisvielSearch.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace glasssix::irisviel;

//fill baseData and queryData from files, erase function body for simplicity
void static loadData(const char* filename, std::vector<const float*> &baseData, unsigned baseNumItem,
	std::vector<const float*> &queryData, unsigned queryNumItem, unsigned dim) {}

int main(int argc, char *argv[])
{
    vector<const float*> baseData;
    vector<const float*> queryData;
    unsigned baseNum = 100000;
    unsigned queryNum = 1000;
    unsigned dimension = 512;
	string nGraphPath = "./ngraph_" + to_string(dimension) + "_" + to_string(baseNum) + ".bin";
	string baseDataSavePath = "./baseData_" + to_string(dimension) + "_" + to_string(baseNum) + ".bin";
	string resultPath = "./result_" + to_string(dimension) + "_" + to_string(baseNum) + ".bin";
    string sourceDataPath = "./map512.bin";
	
    //fill baseData and queryData
    loadData(sourceDataPath.c_str(), baseData, baseNum, queryData, queryNum, dimension);
    
    //construct with both baseData and dimension
    IrisvielSearch oSearch(&baseData, dimension);
	oSearch.buildGraph();
	
	////also we can construct with dimension, then import baseData when buildGraph()
	//IrisvielSearch oSearch(dimension);
	//oSearch.buildGraph(&baseData);
	
	//save both ngraph and baseData, before invoke optimizeGraph()
	oSearch.saveGraph(nGraphPath, baseDataSavePath);
	
    ////also we can only save ngraph, before invoke optimizeGraph()
	//oSearch.saveGraph(nGraphPath);
	
    unsigned topK = 10;//topK cannot exceed the total number in baseData
    std::vector<std::vector<unsigned>> returnIDs;//face IDs returned，returnIDs.size() = queryNum, returnIDs[i].size()=topK
    std::vector<std::vector<float>> returnDistancesInPercentage;//similarity,returnDistancesInPercentage.size()=queryNum,returnDistancesInPercentage[i].size()=topK
    
	oSearch.optimizeGraph();
    oSearch.searchVector(&queryData, topK, returnIDs, returnDistancesInPercentage);
    oSearch.saveResult(resultPath, returnIDs);//only face IDs are saved, similarity ignored 
    
    return 0;
}
```

#### Example Code 4th: Size of image library is larger than 1. Load ngraph from disk, then search. Image library should remain the same when ngraph was generated.
```c++
#include "Irisviel/IrisvielSearch.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace glasssix::irisviel;

//fill baseData or queryData from files
void static loadData(const char* filename, std::vector<const float*> &data, unsigned numItem, unsigned dim) 
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (!in.is_open())
	{
		std::cout << "open file error" << std::endl; exit(-1);
	}
	in.seekg(0, std::ios::beg);
	for (int i = 0; i < numItem; ++i)
	{
		float *temp_data = (float*)malloc(dim * sizeof(float));
		in.read((char*)(temp_data), dim * sizeof(float));
		data.push_back(const_cast<const float*>(temp_data));
	}
	in.close();
}

int main(int argc, char *argv[])
{
    vector<const float*> baseData;
    vector<const float*> queryData;
    unsigned baseNum = 100000;
    unsigned queryNum = 1000;
    unsigned dimension = 512;
	string nGraphPath = "./ngraph_" + to_string(dimension) + "_" + to_string(baseNum) + ".bin";
	string baseDataSavePath = "./baseData_" + to_string(dimension) + "_" + to_string(baseNum) + ".bin";
	string resultPath = "./result_" + to_string(dimension) + "_" + to_string(baseNum) + ".bin";
	string sourceDataPath = "./map512.bin";
	
    //fill baseData and queryData
    loadData(baseDataSavePath.c_str(), baseData, baseNum, dimension);
	loadData(sourceDataPath.c_str(), queryData, queryNum, dimension);
    
    //also we can construct with dimension, then import baseData when loadGraph()
	IrisvielSearch oSearch(dimension);
	oSearch.loadGraph(nGraphPath, baseData);
	
    ////construct with both baseData and dimension
    //IrisvielSearch oSearch(&baseData, dimension);
    //oSearch.loadGraph(nGraphPath);

    unsigned topK = 10;//topK cannot exceed the total number in baseData
    std::vector<std::vector<unsigned>> returnIDs;//face IDs returned，returnIDs.size() = queryNum, returnIDs[i].size()=topK
    std::vector<std::vector<float>> returnDistancesInPercentage;//similarity,returnDistancesInPercentage.size()=queryNum,returnDistancesInPercentage[i].size()=topK
    
	oSearch.optimizeGraph();
    oSearch.searchVector(&queryData, topK, returnIDs, returnDistancesInPercentage);
    oSearch.saveResult(resultPath, returnIDs);//only face IDs are saved, similarity ignored 
    
    return 0;
}
```



#### Class Description: IrisvielSearch

##### Member Function`IrisvielSearch(int dimension);`
Capability: Construct class Index with dimension

Parameter|Parameter Type|Value|Illustration|Remark
:--:|:--:|:--:|:--:|:--:
dimension|int|length of single face feature vector|||

##### Member Function`IrisvielSearch(const std::vector<const float*> *baseData, int dimension);`
Capability: Construct class Index with baseData and dimension

Parameter|Parameter Type|Value|Illustration|Remark
:--:|:--:|:--:|:--:|:--:
baseData|const std::vector<const float*> *|user input|image library|
dimension|int|length of single face feature vector|||

##### Member Function`BuildGraph();`
Capability: build nGraph

##### Member Function`BuildGraph(const std::vector<const float*> *baseData);`
Capability: build nGraph with baseData

Parameter|Parameter Type|Value|Illustration|Remark
:--:|:--:|:--:|:--:|:--:
baseData|const std::vector<const float*> *|user input|image library|

##### Member Function`void SaveGraph(const char *graphPath);`
Capability: save nGraph for future use

Parameter|Parameter Type|Value|Illustration|Remark
:--:|:--:|:--:|:--:|:--:
graphPath|const char *|user input|path of nGraph to be saved|

##### Member Function`void SaveGraph(const char *graphPath, const char *basedataPath);`
Capability: save nGraph and baseData for future use

Parameter|Parameter Type|Value|Illustration|Remark
:--:|:--:|:--:|:--:|:--:
graphPath|const char *|user input|path of nGraph to be saved|
basedataPath|const char *|user input|path of baseData to be saved|

##### Member Function`void LoadGraph(const char* graphPath);`
Capability: Load nGraph from disk before search

Parameter|Parameter Type|Value|Illustration|Remark
:--:|:--:|:--:|:--:|:--:
graphPath|const char *|user input|path of nGraph|

##### Member Function`void LoadGraph(const char* graphPath, const char *basedataPath);`
Capability: Load nGraph and baseData from disk before search

Parameter|Parameter Type|Value|Illustration|Remark
:--:|:--:|:--:|:--:|:--:
graphPath|const char *|user input|path of nGraph|
basedataPath|const char *|user input|path of baseData|


##### Member Function`void optimizeGraph();`
Capability: optimize nGraph before search


##### Member Function`void searchVector(const vector<const float*>* queryData, unsigned topK, std::vector<std::vector<unsigned>> &returnIDs, std::vector<std::vector<float>> &returnDistancesInPercentage);`
Capability: execute search task

Parameter|Parameter Type|Value|Illustration|Remark
:--:|:--:|:--:|:--:|:--:
queryData|const vector<const float*>*|user input|faces to be searched|
topK|unsigned|user input|return topK most similar results for each face|topK should be less than baseNum. If only 1 image exists in image library, execute face verification task(1:1 search), and topK will be useless in this situation.
returnIDs|std::vector<std::vector<unsigned>>|sequence number of baseData, such as 0,1,2,3···|IDs for topK most similar results in baseData|
returnDistancesInPercentage|std::vector<std::vector<float>>|float value between 0 and 1|similarity(L2,Cosine...) of returned topK most similar results| |
		

##### Member Function`void SaveResult(const char* resultPath, std::vector<std::vector<unsigned> > &returnIDs);`
Capability: save IDs of topK most similar results

Parameter|Parameter Type|Value|Illustration|Remark
:--:|:--:|:--:|:--:|:--:
resultPath|const char*|user input|path of returnIDs to be saved|
returnIDs|std::vector<std::vector<unsigned>>|sequence number of baseData, such as 0,1,2,3···| |

##### Member Function`void SaveResult(std::string resultPath, std::vector<std::vector<unsigned> > &returnIDs);`
Capability: save IDs of topK most similar results

Parameter|Parameter Type|Value|Illustration|Remark
:--:|:--:|:--:|:--:|:--:
resultPath|std::string|user input|path of returnIDs to be saved|
returnIDs|std::vector<std::vector<unsigned>>|sequence number of baseData, such as 0,1,2,3···| |

#### Irisviel Performance
Test 128-dimension feature vector on platform i7-8700K, with baseNum of 1K,2K,5K,10K,20K,50K,100K,200K,500K(k represents 1000), queryNum is one tenth of baseNum, return top 10 most similar results for each searched face. Accuracy is calculated by compare our results with time-consuming-brute-force results.
##### Basic Information of Test Platform
Item | Description
:-:|:-:
Operating System | Windows 10 Enterprise 64bit |
Processor | Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz |
Core and Thread | 6 Cores and 12 Threads |
RAM | 32GB |
Compiler | MSVC 19.5 |
OpenMP | Yes |
SIMD Instruction Set | AVX2 |


##### Test Report
baseNum | buildTime(s) | searchTime(ms) | accuracy(\%) | Peak Memory Usage(MB)
:-:|:-:|:-:|:-:|:-:
1k | 0.080 | 0.010 | 100 | 6 | 
2k | 0.141 | 0.015 | 100 | 11 | 
5k | 0.493 | 0.020 | 99.92 | 22 | 
10k | 0.828 | 0.009 | 100 | 41 | 
20k | 1.733 | 0.013 | 99.96 | 68 | 
50k | 4.845 | 0.024 | 99.56 | 177 | 
100k | 20.261 | 0.031 | 99.80 | 375 | 
200k | 71.380 | 0.046 | 99.95 | 753 | 
500k | 221.486 | 0.070 | 98.85 | 2008 | 