# 天问之路

> 虽然没有进入知识星球，但我也很向往这样的记录。在此会记录我自己的“天问之路”

## 第一周（2023.12.25-2023.12.31）

> 主要任务：学习Win32编程，Shellcode，Anti-sandbox

* 先熟悉了一下Win32的API，看了官方文档的桌面向导案例制作一个窗口应用(比c#实现复杂)
* 弄了一下按钮的实现，发现要在WndProc函数处理消息，使用标识符WM_COMMAND来switch case判断
* 出现一个很蠢的bug，读文件会独占，需要关闭Close_Handle。且要设置SE_PRIVILEGE_ENABLED权限才能注入dll [反射dll注入](https://github.com/stephenfewer/ReflectiveDLLInjection)
* 今天早上的安洵杯re题，只看了下皮毛，分别是MFC逆向，GO逆向，Win驱动逆向。一题没解出来。
* 结合了CE修改器以及[植物大战僵尸修改器案例](https://www.bilibili.com/video/BV1pK411w7nw/)视频学会了dll注入后修改基地址变量（简称外挂）遇到问题，必须为常量才能修改生命周期创建在函数调用之前的变量可修改。使用的是WriteProcessMemory函数修改内存。
* 起来给安洵杯的re题都复现了，发现很多盲点，加密算法之类的还是做的题不多。特别是工具，最好去使用Binary Ninja来分析比较好，或者Ghidra，Cutter，Angr。很多IDA的旧版本是无法分辨出符号表以及类型需要自己按Y来定义，比如*(a+i)这玩意是a[i]的意思。~~什么时候才能成为逆向大佬啊~~
* 简单写了一个调用user32.dll的msgboxA函数，对目标程序插桩执行shellcode，或者覆盖返回地址。主要了解了各个系统dll的用处以及适用场景。以及shellcode的加解密调用 ~~（虽然早就用了）~~  主要参考了[51HOOK](https://www.bilibili.com/video/BV1By4y1r7Cq)免费视频来学习
* 今天花了一天的时间将CS配置好了 虽然流量什么的特征估计还存在。但总比裸奔的MSF好！MSF的shellcode非常烂大街，我选择使用CS生成的马进行分析。
* 花了两天把反沙箱完善了，C++真难写。现在可以过国内主流沙箱了，国外其实也可以，但他各种环境不公开，以后可以考虑封IP段来解决。哈哈。
* 国内外沙箱已经完全过了，非常的骚操作。哈哈，但是免杀这里就用了异或加密shellcode而已，加载方式也是注入。不知道能不能过动态咯，最简单的Beacon。

## 第二周（2024.1.1-2024.1.7）

> 主要任务：免杀加强，二开工具，提权相关

* 元旦快乐！
* 隐藏IAT https://www.bordergate.co.uk/import-address-tables/
* CS Beacon 二开 https://tttang.com/archive/1789/
* Fscan 二开 https://cloud.tencent.com/developer/article/2373333
* Mimikatz 二开 免杀 https://blog.csdn.net/zhangshuaiijie/article/details/131350373 https://www.i-monero.com/post/yuan-ma-mian-sha-zhi-mimikatz/
* 提一嘴，360的QVM报毒可以通过添加资源的方式解决...（笑）写了个while(0)给我报QVM。
* 这周也是实训周，写JAVA项目费了点时间。
* 简单弄了一下提权CVE的复现https://i.hacking8.com/tiquan/，以及bypassuac项目的利用https://github.com/hfiref0x/UACME

## 第三周（2024.1.7-2024.1.14）

> 主要任务：复现漏洞

+ 这几天挖了个本校的漏洞，还没过审
+ CVE-2021-44228 Log4j https://www.freebuf.com/vuls/382838.html https://ctf.show/challenges#Log4j%E5%A4%8D%E7%8E%B0-1730
+ CVE-2023-38831 https://mp.weixin.qq.com/s/zOEwLKKHS11XKVlaE-YtVw
