## Face Search V1.0(TrialFaceSDK)
### Capability Introduction
#### Interface Capability
- **Face Search**: Given a face image, finds the most similar K images from the built face graph.
### Application Scenarios
- When the count of faces equals 1, search the image directly.

    ```SearchVector```

- When the count of faces is greater than 1, build the graph and then search the image.

   ```BuildGraph```->```OptimizeGraph```->```SearchVector```

- When the count of faces is greater than 1, build the graph, save it to the disk and then search the image.

   ```BuildGraph```->```SaveGraph```->```OptimizeGraph```->```SearchVector```

- When the count of faces is greater than 1, load the built graph from the disk and then search the image.
   - Prerequisite: the face graph shall not be changed.

   ```LoadGraph```->```OptimizeGraph```->```SearchVector```

### Examples
#### Example 1：Do the (1:1) Face Verification When the Count of Faces Equals 1.

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

#### Example 2: Build the Graph and Then Search the Image When the Count of Faces Is Greater Than 1.

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

#### Example 3: Build the Graph, Save It to The Disk and Then Search the Image When the Count of Faces Is Greater Than 1.

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

#### Example 4: Load the Built Graph From The Disk and Then Search the Image When the Count of Faces Is Greater Than 1.

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

#### IrisvianSearch Class

##### Property ```static string Version { get; }```

Description: gets the version number of the library.

- Returns: a ```string``` value which contains the version number.

##### Property ```IList<float[]> BaseData { get; }```

Description: gets the loaded base data.

- Returns: an ```IList<float[]>``` value which contains the base data.

##### Constructor ```public IrisvianSearch(int dimension)```

Description: creates an instance with the dimension of the feature vector.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|dimension|```int```|User Input|The dimension of the feature vector| |

##### Constructor ```public IrisvianSearch(IList<float[]> baseData, int dimension)```

Description: creates an instance with the base data and the dimension of the feature vector.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|baseData|```IList<float[]>```|User Input|The base data| |
|dimension|```int```|User Input|The dimension of the feature vector| |

##### Method ```public int BuildGraph()```

Description: builds the graph of the loaded base data.

- Returns: an ```int``` value that reveals the memory peak during the calculation (in bytes).

##### Method ```public int BuildGraph(IList<float[]> baseData)```

Description: builds the graph of the base data.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|baseData|```IList<float[]>```|User Input|The base data| |

- Returns: an ```int``` value that reveals the memory peak during the calculation (in bytes).

##### Method ```public void SaveGraph(string path)```

Description: saves the built graph.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|path|```string```|User Input|The save path| |

##### Method ```public void SaveGraph(string graphPath, string baseDataPath)```

Description: saves the built graph and the loaded base data.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|graphPath|```string```|User Input|The saving path of the graph| |
|baseDataPath|```string```|User Input|The saving path of the base data| |

##### Method ```public void LoadGraph(string path)```

Description: loads the built graph from the disk.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|path|```string```|User Input|The path of the graph| |

##### Method ```public void OptimizeGraph()```

Description: optimizes the loaded graph.

##### Method ```public uint[][] SearchVector(IList<float[]> queryData, uint topK, out float[][] returnSimilarities)```

Description: searches one or more features.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|queryData|```IList<float[]>```|User Input|The feature list to search| |
|topK|```uint```|User Input|The top K in the order of similarities| |
|returnSimilarities|```float[][]```|User Input|A buffer to accommodate the similarities| |

- Returns: an ```uint[][]``` value that contains each index of the images.

##### Method ```public void SaveResult(string path, uint[][] result)```

Description: saves the search result to the disk.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|path|```string```|User Input|The saving path| |
|result|```uint[][]```|User Input|The search result| |

#### Irisviel Performance

Given several 128-dimensional vectors on Platform i8-8700K, whose base data are filled with amounts of 1K, 2K, 5K, 10K, 20K, 50K, 100K, 200K, 500K (known as ```baseNum```, 1K = 1,000), it fetches 10 results in descending order of similarities per each vector, when the amount of data to be queried (```queryNum```) is one tenth of the amount of base data (```baseNum```). Then, it compares the 10 results with the accurate values from violent search to calculate the accuracies, which can export the search duration per each vector by dividing the total time of searching by the amount of query data (```queryNum```).

##### Platform Information
Item | Description
:-:|:-:
Operating System | Windows 10 Enterprise 64bit |
Processor | Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz |
Core and Thread | 6 Cores and 12 Threads |
RAM | 32GB |
Compiler | MSVC 19.5 |
OpenMP | Yes |
SIMD Instruction Set | AVX2 |


##### Test Results
Amount | Building Time (s) | Search Time (ms) | Accuracy (\%) | Memory Peak (MB)
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