# TheColdWorldConfigEditer
## A solution that stores settings in a file
## 一种将设置储存在文件的解决方案
## Auther:TheColdWorld

# Set the file format

```
Headle:
{
key=value
}
```

# How to use
使用方法

### Step 1
Go to the [Releases](https://github.com/TheColdWorld/TheColdWorldConfigEditer/releases) page to download the latest DLL file
前往[Releases](https://github.com/TheColdWorld/TheColdWorldConfigEditer/releases)页面下载最新的Dll文件

Or clone the project
或者将项目克隆下来

### Step 2
Create a .NET application
创建一个.NET应用程序

### Step 3

Open "Reference Manager"
打开 "引用管理器"

Click "Browse"
单击 "浏览"

In the pop-up window, select the downloaded DLL file
在弹出的窗口选择下载的dll文件
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