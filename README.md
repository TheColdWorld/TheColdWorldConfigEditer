# TheColdWorldConfigEditer
## A solution that stores settings in a file
# moved to [TCWCE-Project](https://github.com/TheColdWorld/TCWCE-Project)
## 一种将设置储存在文件的解决方案
## Auther:TheColdWorld
# Python part cannot use!
# Set the file format

```
Headle:
{
key=value
}
```

# How to use
使用方法

## C#
### Step 1
Go to the [Releases](https://github.com/TheColdWorld/TheColdWorldConfigEditer/releases) page to download the latest DLL file
前往[Releases](https://github.com/TheColdWorld/TheColdWorldConfigEditer/releases)页面下载最新的Dll文件

Or clone the project
或者将项目克隆下来

### Step 2
Create a .NET application
创建一个.NET应用程序

### Step 3(Download the dll file)

Open "Reference Manager"
打开 "引用管理器"

Click "Browse"
单击 "浏览"

In the pop-up window, select the downloaded DLL file
在弹出的窗口选择下载的dll文件

Click "Add"
单击 " 添加"

Like this:
像这样:
![这样](/Readme_Imgs/Img1.png "这样")

### Step 3(clone the project)
Copy "/CSharp/TheColdWorldConfigEditer" to your project directory
将 "/CSharp/TheColdWorldConfigEditer" 复制到你的项目目录
![这样](/Readme_Imgs/Img2.png "这样")

Your project folder should look like this:
你的项目文件夹应该是这样的:
![这样](/Readme_Imgs/Img3.png "这样")

Follow the following image:
按照下图操作:
![这样](/Readme_Imgs/Img4.png "这样")

In the pop-up window, select the .csproj file in the copied folder
在弹出的窗口选择复制的文件夹中的.csproj文件
![这样](/Readme_Imgs/Img5.png "这样")
这样之后，你的解决方案资源管理器应该有以下内容
![内容](/Readme_Imgs/Img6.png "内容")

将项目添加，像这样
Add the project, like this
![这样](/Readme_Imgs/Img7.png "这样")

### Step 4

#### Method one / 方案1
Add the following code to all your .cs files(Not recommended):
在你的所有.cs文件添加以下代码(不建议):
```c#
using TheColdWorldConfigEditer_Csharp;
```

Or a namespace with "TheColdWorldConfigEditer_Csharp" when you use it, here is an example:
或者在你使用的时候带 "TheColdWorldConfigEditer_Csharp" 的命名空间,以下是一个例子:
```c#
TheColdWorldConfigEditer_Csharp.For_String.Header Headers = new TheColdWorldConfigEditer_Csharp.For_String.Header("41", new TheColdWorldConfigEditer_Csharp.For_String.Key[] { new TheColdWorldConfigEditer_Csharp.For_String.Key("key1", new TheColdWorldConfigEditer_Csharp.For_String.Value("1")) });
```
### At this point, you can use it
### 至此，你可以使用它了

# About bug and recommendations
# 关于漏洞以及建议
Go to the [issues](https://github.com/TheColdWorld/TheColdWorldConfigEditer/issues) page to submit an issue
前往[issues](https://github.com/TheColdWorld/TheColdWorldConfigEditer/issues)页面提交问题

如果你在复制项目后生成出现命名空间缺失问题，也请提交一个[issue](https://github.com/TheColdWorld/TheColdWorldConfigEditer/issues)
If you have a missing namespace issue in your build after copying your project, please also file an [issue](https://github.com/TheColdWorld/TheColdWorldConfigEditer/issues)
