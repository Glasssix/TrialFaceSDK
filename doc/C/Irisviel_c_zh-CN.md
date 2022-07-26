## 人脸搜索V1.0(TrialFaceSDK)
### 接口功能
>人脸搜索: 给定一张人脸图片，从人脸库中找出最相似的K张图片，K值可修改。
>#### 速览: IrisvielSearch
| 核心函数 | 功能  |  返回值  |
|  :--------:   |  :--------:  | :--------:  |
| Irisviel\_save\_path    | 获取maping文件存储目录 |  mapping文件<br>存储目录字符串首地址 |
| Irisviel\_tmp\_path        |   获取build缓存文件存储目录|  build缓存文件存储目录字符串首地址  |
| Irisviel\_build       |   构建人脸搜索库|  mapping文件存储目录字符串首地址|
| Irisviel\_search       |   搜索人员信息|  搜索到的项目个数 |
| Irisviel\_remove_all       |  清空整个数据库| |
| Irisviel\_delet\_features        |  批量删除keys对应的人员信息|    |
| Irisviel\_delet\_feature        |   删除key所对应的人员信息|   |
| Irisviel\_add\_features        |   批量添加人员信息|    |
| Irisviel\_add\_feature        |  添加单个人员信息|    |
| Irisviel\_update\_more        |  批量更新人员信息|    |
| Irisviel\_update\_feature        | 更新一个人员信息|    |

#### 示例代码
```c
#include<dlfcn.h>
#include <iostream>
#include "../../include/Irisviel/knn_service.hpp"

using namespace glasssix::irisviel;

typedef void *(*InstanceFunc)(int, char *, char *);
typedef void (*ReleaseFunc)(void *);
typedef void (*buildFunc)(void *, int, char *[]);
typedef int (*searchFunc)(void *, void **, float *, int);
typedef void (*add_features_Func)(void *, int, void *);

int main(int argc, char *argv[])
{   
	//打开动态链接库 
	void *lib = dlopen(argv[1], RTLD_NOW);
	if(lib)
	{
		std::cout << argv[1] << ", dlopen succeed!" << std::endl;
		char *instance_name = "Irisvian_NewInstance";
		InstanceFunc instance = dlsym(lib, instance_name);
		
		if(instance)
		{
			std::cout << instance_name << " found!" << std::endl;
			//创建一个irisviel类的实例
			void *irisvian = instance(1000, "save", "tmp");
			
			//新增人员信息
			char *add_features_name = "Irisvian_add_features";
			add_features_Func add_features = dlsym(lib, add_features_name);
			if(add_features)
			{
				std::cout << add_features_name << " found!" << std::endl;
				
				knn_mapping_data data[5];
				for(int i = 0; i < 5; i ++)
				{
					for(int j = 0; j < 128; j++)
					data[i].feature[j] = i * 128 + j;
					
					std::string key = "feature" + std::to_string(i);
					std::copy(key.begin(), key.end(), data[i].key);
				}
				
				add_features(irisvian, 5, data);
				std::cout << add_features_name << " " << sizeof(data) << " finished!" << std::endl;
				
				//构建人脸搜索库
				char *build_name = "Irisvian_build";
				buildFunc build = dlsym(lib, build_name);
				if(build)
				{
					build(irisvian, 0, nullptr);
					std::cout << build_name << " finished!" << std::endl;
					
					char *search_name = "Irisvian_search";
					searchFunc search = dlsym(lib, search_name);
					if(search)
					{
						knn_search_result *result;
						float feature[128];
						for(int i = 0; i < 128; i++)
						feature[i] = i;
						
						int result_num = search(irisvian, &result, feature, 2);
						for(int i = 0; i < result_num; i++)
						{
							std::cout << result[i].data.key << ":" << std::endl;
							for(int j = 0; j < 128; j++)
							std::cout << result[i].data.feature[j] << ",";
							std::cout << std::endl;
							std::cout << result[i].distance_in_percentage << std::endl << std::endl;
						}
						std:: cout << search_name << " finished!" << std::endl;
					}
				}				
			}
		}
		dlclose(lib);
	}
	else
	std::cout << argv[1] << ", dlopen failed, " << dlerror() << std::endl;
	
	return 0;
}


```

#### 类名：IrisvielSearch
##### 成员函数 ：knn\_service* Irisviel\_NewInstance(int max_items, char* new_save_path, char* tmp_path);
##### 功能：得到一个IrisvielSearch类的实例
##### 返回值：实例指针

##### 成员函数 ：void Irisviel_ReleaseInstance(knn\_service *instance);
##### 功能：释放一个IrisvielSearch类的实例

##### 成员函数 ：char *Irisviel_save\_path(knn\_service *instance)
##### 功能：获取maping文件存储目录
##### 返回值：mapping文件存储目录字符串首地址

##### 成员函数 ：char *Irisviel_tmp\_path(knn\_service *instance)
##### 功能：获取build缓存文件存储目录
##### 返回值：build缓存文件存储目录字符串首地址
		
##### 成员函数 ：void Irisviel\_build(knn\_service *instance,int n\_files, char *str\_files[]);
##### 功能：构建人脸搜索库

##### 成员函数 ：int Irisviel\_search(knn\_service *instance,knn\_search\_result * * result, float *feature, int top)
##### 功能：搜索人员信息
##### 返回值：搜索到的项目个数

##### 成员函数 ：void Irisviel\_remove\_all(knn\_service *instance)
##### 功能：清空整个数据库

##### 成员函数 ：void Irisviel\_delet\_features(knn\_service *instance,int *needs\_delete\_files\_num, char **needs\_delete\_files[], int keys\_num,char *keys[])
##### 功能：批量删除keys对应的人员信息

##### 成员函数 ：void Irisviel\_delet\_feature(knn\_service *instance,int *needs\_delete\_files\_num, char **needs\_delete\_files[], int keys\_num,char *keys)
##### 功能：删除key所对应的人员信息

##### 成员函数 ：void Irisviel\_add\_features(knn\_service *instance,int data\_num , knn\_mapping\_data *data)
##### 功能：批量添加人员信息

##### 成员函数 ：void Irisviel\_add\_feature(knn\_service *instance,int data\_num , knn\_mapping\_data &data)
##### 功能：添加单个人员信息

##### 成员函数 ：void Irisviel\_update\_more(knn\_service *instance,int data\_num\, knn\_mapping\_data *data);
##### 功能：批量更新人员信息

##### 成员函数 ：void Irisviel\_update\_feature(knn\_service *instance, knn\_mapping\_data \&data); 
##### 功能：更新一个人员信息

|参数|参数类型|值|说明|备注|
|:--------:|:--------:|:--------:|:--------:|:--------:|
|instance|`knn_service*`||指向IrisvielSearch实例的指针| |
|max\_items|int|用户输入|单个mapping文件最大存放数量| |
|new\_save\_path|char*|用户输入|mapping文件存储目录| |
|tmp\_path|char*|用户输入|build缓存文件存储目录| |
|n\_files|int||mapping文件个数||
|str\_files[]|char*||指向存放多个mapping文件路径字符串数组首地址||
|result|`knn_search_result **`|接收输出的搜索结果<br>指向knn\_search\_result数组的首地址||
|feature|floa*||128维特征向量||
|top|int||指示输出最相似的前top个项目||
|needs\_delete\_files\_num|`int *`||指向接收输出的删除文件数量的地址| |
|needs\_delete\_files[]|`char **`||接收输出的删除文件路径指向<br>多个文件路径字符串首地址数组的首地址| |
|keys\_num|int||待删除key集合数量| |
|keys[]|`char *`||待删除的key集合| |
|key|`char *`||待删除的key| |
|data\_num|int|用户输入|待添加的特征个数| |
|data|`knn_mapping_data * `||指向待添加的knn\_mapping\_data数组的首地址| |
|data|`knn_mapping_data & `||一个knn\_mapping\_data变量的引用| |

### 依赖项
>CPU: MSVCP140、VCRUNTIME140 

### 性能测试

##### 测试平台基本信息
|项目 | 描述|
|:-:|:-:|
|操作系统 | Windows 10 企业版 64位 |
|处理器 | Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz |
|处理器核心数 | 6核12线程 |
|内存 | 32GB |
|编译器 | MSVC 19.5 |
|OpenMP | 开启 |
|SIMD指令集 | AVX2 |
##### Irisviel性能表现
>在i7-8700K平台选取1K,2K,5K,10K,20K,50K,100K,200K,500K的128维基础数据量(baseNum)分别进行测试（K表示1000条）。待查询数据量(queryNum)为基础数据量(baseNum)的十分之一,对每条待查询数据,返回10个相似度最高的结果。将返回的10个结果与通过高耗时暴力搜索方法找到的10个准确值进行对比，计算得到准确率。再用执行搜索任务的总时间除以查询数据量(queryNum)，得到每条数据的搜索时间。

数据量 | 构建时间(s) | 搜索时间(ms) | 准确率(\%) | 峰值内存(MB)
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
