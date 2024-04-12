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

+ 这几天挖了几个本校的漏洞，还没过审
+ CVE-2021-44228 Log4j https://www.freebuf.com/vuls/382838.html https://ctf.show/challenges#Log4j%E5%A4%8D%E7%8E%B0-1730
+ CVE-2023-38831 https://mp.weixin.qq.com/s/zOEwLKKHS11XKVlaE-YtVw
+ CVE-2022-4510 Binwalk 2.12b-2.3.3 https://bbs.kanxue.com/thread-276033.htm

## 第四周（2024.1.15-2024.1.21）

> 主要任务：STL容器、科目一

+ 放假了，出去玩
+ 这周因为种种原因摆了好几天
+ 只熟悉了STL各大容器的CRUD和其中注意点 参考https://www.bilibili.com/video/BV1D24y1e7nz/

## 第五周（2024.1.22-2024.1.28）

> 主要任务：~~STL逆向，STL实现~~，软件分析，科目一，软著项目

+ ~~实现参考https://github.com/Alinshans/MyTinySTL https://qlipphoth.github.io/2023/08/19/2023-8-19-1/ https://github.com/Qlipphoth/TinySTL~~
+ ~~逆向参考https://www.52pojie.cn/forum.php?mod=viewthread&tid=1720719 https://bbs.kanxue.com/thread-275133.htm~~
+ *之所以把任务减少了，是因为STL这玩意也太难了，数据结构，C++各种声明我都还没用过*
+ https://ranger-nju.gitbook.io/static-program-analysis-book/
+ https://xiongyingfei.github.io/SA/2022/main.htm
+ 主要花时间看一下 南京大学《软件分析》https://www.bilibili.com/video/BV1b7411K7P4/
+ 这周写C#居多，回归老本行，写C#是真的舒服！

## 第六周（2024.1.29-2024.2.4）

> 主要任务：CodeQL，软件分析，科目一

+ 回家了
+ ~~太过于学术的知识完全学不下去~~

## 第七周（2024.2.5-2024.2.11）

> 主要任务：摆摊、休息、过年

+ 摆摊卖春联（龙年限定）卖不完只能12年后再卖了
+ 摆摊第一天：回本三分之一
+ 摆摊第二天：下雨 回本0
+ 摆摊第三天：回50
+ 摆摊第四天：除夕快乐，准备结束
+ 亏损150人民币

## 第八周（2024.2.12-2024.2.18）

> 主要任务：重拾pwn

+ gdb巩固
+ pip install pip -U
+ pip config set global.index-url https://mirrors.aliyun.com/pypi/simple
+ pip config set install.trusted-host mirrors.aliyun.com

## 第九周（2024.2.19-2024.2.25）

> 主要任务：pwn

+ 刷题以理解做题技巧

## 第十周（2024.2.26-2024.3.3）

> 主要任务：pwn

+ https://www.yuque.com/hxfqg9/

## 第十一周（2024.3.4-2024.3.10）

> 主要任务：备赛国赛、pwn、背单词

+ 堆利用给我整麻了，刷了好多pwn题

## 第十二周（2024.3.11-2024.3.17）

> 主要任务：pwn、备考NISP二级、背单词、准备混hvv

+ 又刷了好多pwn，记一下模板和技巧总结
+ 报考了NISP二级了，一个月后考
+ 不背单词打卡14天完成
+ 重新弄了一下免杀 和c2相关内容（以备混个红？
+ 钓鱼 https://blog.csdn.net/qq_42939527/article/details/107485116
+ 早起纳新赛坐牢了
+ pwn和re虽然是我的方向，但这也太打击人了。每场比赛都0解。
+ 复盘了一下，re解出来一半...但第二题就是VM，裂开

## 第十三周（2024.3.18-2024.3.24）

> 主要任务：re、pwn、争取hw！、读文章

+ 准备看的文章
  + https://xz.aliyun.com/t/13592 域渗透票据
  + https://xz.aliyun.com/t/12498 域渗透隧道
  + https://xz.aliyun.com/t/14075 白加黑
  + https://xz.aliyun.com/t/14076 后渗透
+ 简单搞了一下re题的算法和标识的笔记 待完善...
+ 准备给软路由加个ARL https://github.com/TophantTechnology/ARL
+ https://zhuanlan.zhihu.com/p/656652577 PVE加装WIFI
+ https://github.com/Neo-Maoku/DllMainHijacking
+ https://zhuanlan.zhihu.com/p/578966149
+ ~~学一下z3的具体解法~~还是不会

## 第十四周（2024.3.25-2024.3.31）

> 主要任务：re、备国赛、争取hvv、web
>
> 这周末要长城杯了 且24届的专升本也开考了 祝所有人顺利

+ 写了下远程下载的马，被360QVM杀了，下载到本地这个create一个file流的操作还是太敏感了
+ 总结下自己写的免杀方案吧(粗略)
  + 单文件
    + 反沙箱(time,ip,ram,cpu,disk...)
    + shellcode加密(xor,aes,des...)
    + 少见的内存alloc函数 并且自己typedefine一个struct函数用
    + 关键字符串进行执行时解密防止静态扫描到
    + 给关键代码行添加junkcode
    + 注入线程防止留下不可靠的pid，用可靠的ppid
    + 加壳
  + 多文件
    + 白加黑
    + 远程下载执行
+ https://forum.butian.net/share/2772 看到一个远程下载bypass的思路 准备实践
  + 实现了 挺好用的 就是会有浏览器窗口的打开
+ https://forum.butian.net/share/2669 看到一个免杀相关思路 准备实践
  + 答辩文章
  + 但发现一个好网站https://www.ired.team/
+ https://forum.butian.net/share/2778 看到一个挖支付相关漏洞的思路 准备做笔记
  + 比较不详细，但总结的还行
+ 报名了英语六级，6月15日考试，不知道会不会和国赛冲突，没事，激励自己学习的动力！
+ 写了一个动态调试的re题目 比较有趣 https://www.nssctf.cn/note/set/6182
+ 剩下的时间复习点web吧，毕竟作为CTF的大头方向
+ 长城杯web 0解 虽然简单 但是真没花时间去 而且也中道崩殂 但是也勉强进了半决赛了
+ 专升本下次就到我了，有点紧张。总感觉这周很漫长，也许是漫无目的的原因，希望四月顺利！

## 第十五周（2024.4.1-2024.4.7）

> 打比赛、复习NISP二级、争取hvv、re、pwn

+ https://xz.aliyun.com/t/14215
  + 一个免杀总结
+ https://xz.aliyun.com/t/14201
  + C2 识别 考虑复现
  + 答辩，简短没啥用，像是FOFA的广告
+ 红明谷说实话有点可惜，第36名，自己还是太菜了。misc crypto web，就是没有re...
+ hvv相关的东西还是需要掌握完全一点，毕竟自己的经验实在是太少了（没有人脉）
+ 祝大家清明安康！
+ https://xz.aliyun.com/t/14234
  + c2 识别 赛题
+ https://ctf.0xff.re/ CTFreWP
+ fuzz https://www.cnblogs.com/cx1ng
+ binary exp https://bbs.kanxue.com/homepage-930159.htm
+ SMC SEH
+ https://bbs.kanxue.com/thread-271891.htm linux 异常处理隐藏bytes
+ 莫名其妙的突然想出题，出了两道web一道re，算了以后再次举办比赛的时候再出吧，耗费时间
  + 3web 3crypto 3re 4misc
+ https://xz.aliyun.com/t/12808
  + 内存马查杀工具
+ https://github.com/Getshell/Mshell
+ https://blog.csdn.net/snowlyzz/article/details/128695272
+ http://47.108.150.136:8080/IDS/

## 第十六周（2024.4.8-2024.4.14）

> 临近NISP二级备考、hvv、re、应急响应、iotcve复现

+ war包木马部署 jar cvf test.war test.jsp
+ hifish
+ https://xz.aliyun.com/t/13839 内网相关
+ https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2024-28354
+ https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2024-29385
  + https://shadowfile.inode.link/blog/2013/02/dlink-dir-815-upnp-command-injection/
+ https://paper.seebug.org/2071/
