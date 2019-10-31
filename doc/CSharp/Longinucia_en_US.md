## Face Recognition V1.0(TrialFaceSDK)
### Capability Introduction
#### Interface Capability
- **Face Detection**：Invokes face detection on the input grayscale bitmap and locates the faces.
#### Dependencies
- **CPU**：
   - MSVCP141
   - VCRUNTIME141
   - .Net Framework 4.6.2
### Examples
#### Example 1
```C#
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using glasssix.longinus;

namespace CSharpExample
{
    class Program
    {
        static void Main(string[] args)
        {
            int device = -1;
            Bitmap bmp = new Bitmap(@"D:\720.jpg");
            Longinucia longinucia = new Longinucia();
            longinucia.set(DetectorType.MULTIVIEW_REINFORCE, device);
            var res = longinucia.Face_Detect(bmp, 24, 1.1f, 3, false, false, true);

            var aligned_faces = longinucia.AlignFace(bmp, res);
            for (int i = 0; i < aligned_faces.Length; i++)
            {
                aligned_faces[i].Save(@"D:\720_align" + i + ".jpg");
            }

            for (int i = 0; i < res.Count; i++)
            {
                DrawRectangleInPicture(bmp,
                    new Rectangle(res[i].rect.X, res[i].rect.Y, res[i].rect.Width, res[i].rect.Height), Color.Azure, 2,
                    DashStyle.Dash);
            }
            bmp.Save(@"D:\720_res.jpg");

            return;
        }

        public static Bitmap DrawRectangleInPicture(Bitmap bmp, Rectangle rect, Color RectColor, int LineWidth, DashStyle ds)
        {
            if (bmp == null) return null;
            Graphics g = Graphics.FromImage(bmp);
            Brush brush = new SolidBrush(RectColor);
            Pen pen = new Pen(brush, LineWidth);
            pen.DashStyle = ds;
            g.DrawRectangle(pen, rect);
            g.Dispose();
            return bmp;
        }
    }
}
```

#### ```Longinucia``` Class
##### Constructor ```public Longinucia()```
Description: creates an instance.

##### Constructor ```public Longinucia(int width, int height)```
Description: creates an instance with the specified width and height in pixels.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|width|```int```|User Input|The width in pixels||
|height|```int```|User Input|The height in pixels||

##### Method ```public void set(DetectorType type, int device)```
Description: sets the method of detection.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|type|```DetectorType```|FRONTALVIEW<br>FRONTALVIEW_REINFORCE<br>MULTIVIEW<br> MULTIVIEW_REINFORCE|The values is arranged in descending order of speed.||
|device|```int```|```<0```<br>```>=0```|Sets the CPU as the physical device.<br>Sets the GPU as the physical device.| |

##### Method ```public List<FaceInfo> Face_Detect(Bitmap bmp, int min_size, float scale, int minNeighbors, bool useMultiThreads, bool doEarlyReject, bool doLandmark)```
Description: invokes face detection on the input grayscale bitmap and locates the faces.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|bmp|```Bitmap```|User Input|The grayscale bitmap||
|minSize|```int```|```>=24```|The smallest window size of detection|The rectangle size of a detected face is ```>= minSize``` .|
|scale|```float```|```> 1```|The scaling ratio of the image|Generally ```> 1.1```|
|minNeighbors|```int```|```>=0```|The candidate boxes around the face rectangle|Generally set to 3|
|useMultiThreads|```bool```|```true```<br>```false```|Multithreaded<br>Single-threaded|Only effecitve when the device is less than zero. The default is ```false``` .|
|doEarlyReject|```bool```|```true```<br>```false```|Does early rejections<br>Skips early rejections|Speeds up the detection when set to ```true``` with a decreasing quality; otherwise the opposite. The default is ```false``` .|

- Returns: a ```List<FaceInfo>``` which contains information about detected faces.

##### Method ```public void set(DetectorType type, int device)```
Description: sets the method of detection.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|type|```DetectorType```|FRONTALVIEW<br>FRONTALVIEW_REINFORCE<br>MULTIVIEW<br> MULTIVIEW_REINFORCE|The values is arranged in descending order of speed.||
|device|```int```|```<0```<br>```>=0```|Sets the CPU as the physical device.<br>Sets the GPU as the physical device.| |

##### Method ```public Bitmap[] AlignFace(Bitmap bmp, List<FaceInfo> infos)```
Description: align detected faces.

|Name|Type|Value|Description|Remark|
|:---:|:---:|:---:|:---:|:---:|
|bmp|```Bitmap```|User Input|The grayscale bitmap, same with Face_Detect method||
|infos|```List<FaceInfo>```||information about detected faces|The returned value of Face_Detect.|

- Returns: an array of ```Bitmap``` which contains aligned faces, image size is 3*128*128(channel,height,width).

#### Longinus Performance
The following table reveals the testing results deduced by calculating the average time of 1,000-time extractions on three images (640 \* 480、1280 \* 720 and 1920 \* 1080), on Platform i7-8700K.

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

Parameter: minSize=48, scale=1.2, minNeighbors=3, useMultiThreads=false, doEarlyReject=false

Detection Time (ms)：

Size | FRONTALVIEW | FRONTALVIEW_REINFORCE | MULTIVIEW | MULTIVIEW_REINFORCE
:-:|:-:|:-:|:-:|:-:
640 * 480 | 11.72 | 25.72 | 34.06 | 41.42 |
1280 * 720 | 26.14 | 45.44 | 69.09 | 85.07 |
1920 * 1080 | 76.59 | 122.38 | 155.89 | 186.86 |

![avatar](../640.jpg)
![avatar](../720.jpg)
![avatar](../1080.jpg)

Content Disclaimer: The test images are downloaded from the Internet and the copyright belongs to the original author. If there is any infringement, please contact me to delete the contents. Thank you.