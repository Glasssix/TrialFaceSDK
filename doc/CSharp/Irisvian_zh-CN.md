## 人脸搜索V1.0（TrialFaceSDK）
### 能力介绍
#### 接口能力
- **人脸搜索**: 给定一张人脸图片，从人脸库中找出最相似的 K 张图片，K 值可修改。
### 使用场景
- 人脸库数量等于 1：直接执行搜索。

    ```SearchVector```

- 人脸库数量大于 1：构建并搜索，不保存构建的图。

   ```BuildGraph```->```OptimizeGraph```->```SearchVector```

- 人脸库数量大于 1：构建并保存构建的图，然后执行搜索。

   ```BuildGraph```->```SaveGraph```->```OptimizeGraph```->```SearchVector```

- 人脸库数量大于 1：不构建，从磁盘读取已构建的图，然后执行搜索。
   - 前提条件：人脸库未发生变化。

   ```LoadGraph```->```OptimizeGraph```->```SearchVector```

### 调用方式
#### 示例代码一：人脸库数量等于 1，直接调用 ```SearchVector``` 进行人脸验证（1 : 1）

```C#
using System;
using glasssix::gaius;

internal class Program
{
	static void Main(string[] args)
	{

	}
}
```

#### 示例代码二：人脸库数量大于 1，构建图，然后执行搜索。
```C#
using System;
using glasssix::gaius;

internal class Program
{
	static void Main(string[] args)
	{

	}
}
```

#### 示例代码三：人脸库数量大于 1，构建并保存构建的图，然后执行搜索。
```C#
using System;
using glasssix::gaius;

internal class Program
{
	static void Main(string[] args)
	{

	}
}
```

#### 示例代码四：人脸库数量大于 1，不构建，从磁盘读取已构建的图，然后执行搜索。
```C#
using System;
using glasssix::gaius;

internal class Program
{
	static void Main(string[] args)
	{

	}
}
```

#### IrisvianSearch 类

##### 属性 ```static string Version { get; }```
功能：获取当前库的版本号。

- 返回：一个 ```string``` 值，其中包含版本号。

##### 属性 ```IList<float[]> BaseData { get; }```
功能：获取当前已加载的基础数据。

- 返回：```IList<float[]>``` ，其中包含基础数据。

##### 构造函数 ```public IrisvianSearch(int dimension)```
功能：创建一个 IrisvianSearch 类的实例，并指定特征值向量的维数。

|参数|参数类型|值|说明|备注|
|:---:|:---:|:---:|:---:|:---:|
|dimension|```int```|用户输入|特征值向量的维数| |

##### 构造函数 ```public IrisvianSearch(IList<float[]> baseData, int dimension)```
功能：创建一个 IrisvianSearch 类的实例，并指定基础数据和特征值向量的维数。

|参数|参数类型|值|说明|备注|
|:---:|:---:|:---:|:---:|:---:|
|baseData|```IList<float[]>```|用户输入|基础数据| |
|dimension|```int```|用户输入|特征值向量的维数| |

##### 方法 ```public int BuildGraph()```
功能：构建已加载基础数据的图。

- 返回：一个 ```int``` 值，代表计算过程中内存占用峰值（以字节为单位）。

##### 方法 ```public int BuildGraph(IList<float[]> baseData)```
功能：构建基础数据的图。

|参数|参数类型|值|说明|备注|
|:---:|:---:|:---:|:---:|:---:|
|baseData|```IList<float[]>```|用户输入|基础数据| |

- 返回：一个 ```int``` 值，代表计算过程中内存占用峰值（以字节为单位）。

##### 方法 ```public void SaveGraph(string path)```
功能：保存已构建的图。

|参数|参数类型|值|说明|备注|
|:---:|:---:|:---:|:---:|:---:|
|path|```string```|用户输入|保存路径| |

##### 方法 ```public void SaveGraph(string graphPath, string baseDataPath)```
功能：保存已构建的图，并另存基础数据。

|参数|参数类型|值|说明|备注|
|:---:|:---:|:---:|:---:|:---:|
|graphPath|```string```|用户输入|图的保存路径| |
|baseDataPath|```string```|用户输入|基础数据的保存路径| |

##### 方法 ```public void LoadGraph(string path)```
功能：从磁盘加载已构建的图。

|参数|参数类型|值|说明|备注|
|:---:|:---:|:---:|:---:|:---:|
|path|```string```|用户输入|图的路径| |

##### 方法 ```public void OptimizeGraph()```
功能：优化已加载的图。

##### 方法 ```public uint[][] SearchVector(IList<float[]> queryData, uint topK, out float[][] returnSimilarities)```
功能：搜索一个或多个特征值。

|参数|参数类型|值|说明|备注|
|:---:|:---:|:---:|:---:|:---:|
|queryData|```IList<float[]>```|用户输入|要搜索的特征值列表| |
|topK|```uint```|用户输入|按相似度从高到低的前 K 项值| |
|returnSimilarities|```float[][]```|用户输入|存放每个特征值的相似度| |

- 返回：```uint[][]``` ，保存每个特征值对应的库索引。

##### 方法 ```public void SaveResult(string path, uint[][] result)```
功能：把搜索结果保存到磁盘。

|参数|参数类型|值|说明|备注|
|:---:|:---:|:---:|:---:|:---:|
|path|```string```|用户输入|保存路径| |
|result|```uint[][]```|用户输入|搜索结果数组| |

#### Irisviel 性能表现
在 i7-8700K 平台选取 1K, 2K, 5K, 10K, 20K, 50K, 100K, 200K, 500K 的 128 维基础数据量（baseNum）分别进行测试（K 代表 1000）。待查询数据量（queryNum）为基础数据量（baseNum）的十分之一时，对每条待查询数据返回10 个相似度最高的结果。将返回的 10 个结果与通过高耗时暴力搜索方法找到的 10 个准确值进行对比，计算得到准确率。最后使用执行搜索任务的总时间除以查询数据量（queryNum），即得到每条数据的搜索时间。

##### 测试平台基本信息
项目 | 描述
:-:|:-:
操作系统 | Windows 10 企业版 64位 |
处理器 | Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz |
处理器核心数 | 6核12线程 |
内存 | 32GB |
编译器 | MSVC 19.5 |
OpenMP | 开启 |
SIMD 指令集 | AVX2 |


##### 测试结果
数据量 | 构建时间（s） | 搜索时间（ms） | 准确率（\%） | 峰值内存（MB）
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