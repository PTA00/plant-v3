# plant-v3
> 该储存库由[【c语言:carrot:群】](https://jq.qq.com/?_wv=1027&k=PFgXdTWT)构建&维护
> 
> 原始版本作者：[@无敌大菠萝](http://wpa.qq.com/msgrd?v=3&uin=610282681&site=qq&menu=yes)

说明
---

该储存库版本使用vscode编辑和构建

> 原始版本使用devc创建，需要转换为GBK编码，且没有方便的git提交工具，不推荐使用！

* 源码的文本编码为UTF-8，在默认编码页的控制台中会出现乱码。
* 请在工作目录内的配置文件`tasks.json`内的"args"列表中添加编译命令`-fexec-charset=GBK`
* 更改后的args列表应为如下所示：
```
"args": [
    "-fdiagnostics-color=always",
    "-g",
    "${file}",
    "-o",
    "${fileDirname}\\${fileBasenameNoExtension}.exe",
    "-fexec-charset=GBK"
]
```
