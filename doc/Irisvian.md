## 人脸搜索V1.0(TrialFaceSDK)
### 能力介绍
#### 接口能力
- **人脸搜索**: 给定一张人脸图片，从人脸库中找出最相似的K张图片，K值可修改。
### 使用场景
1. 人脸库数量等于1

    直接调用searchVector()

2. 人脸库数量大于1，构建并搜索，不保存构建的ngraph

    buildGraph()->optimizeGraph()->searchVector()

3. 人脸库数量大于1，构建并保存构建的ngraph，然后搜索

    buildGraph()->saveGraph()->optimizeGraph()->searchVector()

4. 人脸库数量大于1，不构建，从本地读取之前构建的ngraph，然后搜索(前提条件：人脸库未发生变化)

    loadGraph()->optimizeGraph()->searchVector()

### 调用方式
#### 示例代码一：人脸库数量等于1,直接调用searchVector()进行人脸验证(face verification 1:1)
```c++
#include "Irisvian/IrisvianSearch.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace glasssix::Irisvian;

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
    
	IrisvianSearch oSearch(&baseData, dimension);
    oSearch.searchVector(&queryData, topK, returnIDs, returnDistancesInPercentage);
    oSearch.saveResult(resultPath, returnIDs);//only face IDs are saved, similarity ignored 
    
    return 0;
}
```

#### 示例代码二：人脸库数量大于1，构建并搜索，不保存构建的ngraph
```c++
#include "Irisvian/IrisvianSearch.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace glasssix::Irisvian;

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
    IrisvianSearch oSearch(&baseData, dimension);
	oSearch.buildGraph();
	
	////also we can construct with dimension, then import baseData when buildGraph()
	//IrisvianSearch oSearch(dimension);
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

#### 示例代码三：人脸库数量大于1，构建并保存构建的ngraph，然后搜索
```c++
#include "Irisvian/IrisvianSearch.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace glasssix::Irisvian;

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
    IrisvianSearch oSearch(&baseData, dimension);
	oSearch.buildGraph();
	
	////also we can construct with dimension, then import baseData when buildGraph()
	//IrisvianSearch oSearch(dimension);
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

#### 示例代码四：人脸库数量大于1，不构建，从本地读取之前构建的ngraph，然后搜索(前提条件：人脸库未发生变化)
```c++
#include "Irisvian/IrisvianSearch.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace glasssix::Irisvian;

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
	IrisvianSearch oSearch(dimension);
	oSearch.loadGraph(nGraphPath, baseData);
	
    ////construct with both baseData and dimension
    //IrisvianSearch oSearch(&baseData, dimension);
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



#### IrisvianSearch类说明

##### 成员函数`IrisvianSearch(int dimension);`
功能: 构造Index类

参数|参数类型|值|说明|备注
:--:|:--:|:--:|:--:|:--:
dimension|int|baseData中单个人脸特征向量的维度|||

##### 成员函数`IrisvianSearch(const std::vector<const float*> *baseData, int dimension);`
功能: 用base_data构造Index类

参数|参数类型|值|说明|备注
:--:|:--:|:--:|:--:|:--:
baseData|const std::vector<const float*> *|用户输入|人脸库数据|用户可通过读取本地文件、数据库等多种方式填充baseData
dimension|int|baseData中单个人脸特征向量的维度|||

##### 成员函数`BuildGraph();`
功能: 构建nGraph

##### 成员函数`BuildGraph(const std::vector<const float*> *baseData);`
功能: 构建nGraph

参数|参数类型|值|说明|备注
:--:|:--:|:--:|:--:|:--:
baseData|const std::vector<const float*> *|用户输入|人脸库数据|用户可通过读取本地文件、数据库等多种方式填充baseData

##### 成员函数`void SaveGraph(const char *graphPath);`
功能: 保存构建完成的nGraph

参数|参数类型|值|说明|备注
:--:|:--:|:--:|:--:|:--:
graphPath|const char *|用户输入|nGraph构建完成后的保存路径|

##### 成员函数`void SaveGraph(const char *graphPath, const char *basedataPath);`
功能: 保存构建完成的nGraph以及baseData

参数|参数类型|值|说明|备注
:--:|:--:|:--:|:--:|:--:
graphPath|const char *|用户输入|nGraph构建完成后的保存路径|
basedataPath|const char *|用户输入|baseData保存路径|

##### 成员函数`void LoadGraph(const char* graphPath);`
功能: 开始搜索前，从本地加载baseData。

参数|参数类型|值|说明|备注
:--:|:--:|:--:|:--:|:--:
graphPath|const char *|用户输入|nGraph构建完成后的保存路径|

##### 成员函数`void LoadGraph(const char* graphPath, const char *basedataPath);`
功能: 开始搜索前，从本地加载baseData。

参数|参数类型|值|说明|备注
:--:|:--:|:--:|:--:|:--:
graphPath|const char *|用户输入|nGraph构建完成后的保存路径|
basedataPath|const char *|用户输入|baseData保存路径|


##### 成员函数`void optimizeGraph();`
功能: 开始搜索前，对nGraph进行优化。


##### 成员函数`void searchVector(const vector<const float*>* queryData, unsigned topK, std::vector<std::vector<unsigned>> &returnIDs, std::vector<std::vector<float>> &returnDistancesInPercentage);`
功能: 执行搜索任务

参数|参数类型|值|说明|备注
:--:|:--:|:--:|:--:|:--:
queryData|const vector<const float*>*|用户输入|待查询的人脸数据|用户可通过读取本地文件、数据库等多种方式填充queryData
topK|unsigned|用户输入|为每个query对象返回topK个最相似结果|topK不应大于人脸库中的数量baseNum；如果人脸库中只有1张人脸，则进行1V1的搜索，此时topK参数无效，可随便指定。
returnIDs|std::vector<std::vector<unsigned>>|输出的ID|在baseData中找到的与queryData相似的人脸的ID|人脸ID在baseData中为0,1,2,3···
returnDistancesInPercentage|std::vector<std::vector<float>>|输出的相似度|在baseData中找到的与queryData相似的人脸的相似度，以百分比表示|
		

##### 成员函数`void SaveResult(const char* resultPath, std::vector<std::vector<unsigned> > &returnIDs);`
功能: 保存搜索得到的人脸ID

参数|参数类型|值|说明|备注
:--:|:--:|:--:|:--:|:--:
resultPath|const char*|用户输入|搜索完成后的保存路径|
returnIDs|std::vector<std::vector<unsigned>>|输出的ID|在baseData中找到的与queryData相似的人脸的ID|

##### 成员函数`void SaveResult(std::string resultPath, std::vector<std::vector<unsigned> > &returnIDs);`
功能: 保存搜索得到的人脸ID

参数|参数类型|值|说明|备注
:--:|:--:|:--:|:--:|:--:
resultPath|std::string|用户输入|搜索完成后的保存路径|
returnIDs|std::vector<std::vector<unsigned>>|输出的ID|在baseData中找到的与queryData相似的人脸的ID|
