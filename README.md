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
  + 更新-没进半决赛，逆天主办方VPN并发只有1000导致赛区人数不准 浙江等大省并入后无法晋级
  + 完全可以让人数平均点，而不是分赛区，难度对我们来说太大了，沿海全是人...明明理论题已经很逆天了
  + 7月吸取教训继续打第二届
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
  + 内存马攻防研究
+ https://blog.csdn.net/snowlyzz/article/details/128695272
  + weblogic T3协议解析 hvv面试需要
+ http://47.108.150.136:8080/IDS/
  + 一个在线流量包检测

## 第十六周（2024.4.8-2024.4.14）

> 临近NISP二级备考、hvv、re、应急响应、iotcve复现

+ war包木马部署 jar cvf test.war test.jsp

  + 备忘一下
+ hifish

  + 实现了，还挺不错的，免费简单快速
+ https://xz.aliyun.com/t/13839 内网相关
+ https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2024-28354
+ https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2024-29385

  + https://shadowfile.inode.link/blog/2013/02/dlink-dir-815-upnp-command-injection/
+ https://paper.seebug.org/2071/

  + iot RCE
+ 提交了几个CVE不知道能不能过，好激动
+ https://cv196082.gitee.io/

  + 博客
+ https://www.cnblogs.com/VxerLee/p/16427304.html

  + iot 包括购买设备
+ https://paper.seebug.org/3137

  + 创宇404貌似是抄别人的，也不标注一下，原来链接找不到了，就记录下这个吧
+ https://zhuanlan.zhihu.com/p/656521191

  + 单网卡多ip 教程
+ 大蒜fuzzer（以后再买）

  + 第一课 RADASM 任意代码执行漏洞 https://mp.weixin.qq.com/s/U9dq7TnfA8AaGsJGeLNu1w
    第二课 第2-4个目标https://mp.weixin.qq.com/s/8LsJGheGSEAjDynvKOj9Hg
    第三课 潜在的文件格式 https://mp.weixin.qq.com/s/XbKfnQm2CxuTXOYtLYxHCw
    第四课  大结局  https://mp.weixin.qq.com/s/XbKfnQm2CxuTXOYtLYxHCw

## 第十七周（2024.4.15-2024.4.21）

> NISP2，hvv准备面试

+ 用findwallet寻找比特币的加密钱包文件
  + npm install findwallet -g
    findwallet -i .
+ https://www.cnblogs.com/rxrxrx/p/rxrxrx.html
  + 面试题
+ https://github.com/webraybtl/PeachFuzzer
+ https://www.cnblogs.com/backlion/p/15840033.html
  + 内网渗透
+ https://blog.csdn.net/lswzw/article/details/101367163
  + 单用户 重置root密码

## 第十八周（2024.4.22-2024.4.28）

> hvv、re、crypto、小工具

+ wmic process where name="target.exe" get CreationDate

  + 查询进程启动时间
+ https://mp.weixin.qq.com/s/fZ64HXkZwXQ-MZYZFGxNTQ

  + 一个SSRF杀穿的靶机wp
+ c2反制

  + https://github.com/ryanohoro/csbruter
  + https://github.com/Potato-py/csIntruder
  + cs<4.7 CVE漏洞
+ https://www.bilibili.com/read/readlist/rl472724

  + rsa相关
+ https://github.com/p1d3er/port_reuse
+ + 端口复用
+ https://github.com/p1d3er/ReuseSocks

  + socks5端口复用
+ https://blog.csdn.net/Sciurdae/article/details/133843931

  + 2023 SWPU NSS reverse wp
+ https://mp.weixin.qq.com/s/bCmEjZ0bQgN5MeFOZm_4_g

  + nginx反代钓鱼
+ https://www.icode9.com/content-1-1126418.html

  + TEA算法 python实现
+ 写的文章通过了，好开心

  + 反沙箱杂谈 求师傅们点个顶！ https://xz.aliyun.com/t/14381

## 第十九周（2024.4.29-2024.5.5）

> 运维安全赛理论、赛题复现、iscc

+ https://cdisk.imxbt.cn/s/jRfM?path=%2F
+ 文章破千阅读量了，庆祝，项目也超10个star了，庆祝！
+ ISCC摆烂中...
+ https://blacknight.notion.site/trick-e971a730c35449888f40d319a1ff8de5

  + 攻防tick

## 第二十周（2024.5.6-2024.5.12）

> 运维安全实践、赛题复现、iscc

+ ok 实践赛也是被判作弊了，就算没作弊也拿不到奖（安慰  赛后复现下有意思的题目吧
+ iscc这周就放题了

  + 放题后排名掉了几十名
+ cve终于弄公开了，浪费好多时间啊（cnvd还没审

  + https://www.tenable.com/cve/CVE-2024-33110
  + https://www.tenable.com/cve/CVE-2024-33112
  + https://www.tenable.com/cve/CVE-2024-33113
  + 高危，33111是XSS罢了
+ https://www.cnblogs.com/zhaotianff/p/13860307.html

  + 删除commit
+ 记录一下nethunter的安装

  + MIUI11 K20PRO尊享版
  + MIUI11 用的是skymiui 酷安上找的
  + 内核 https://github.com/DOITfit/Redmi-K20Pro-Nethunter-Project
    + 适用于k20pro k20 尊享版有bug
  + nethunter https://www.kali.org/get-kali/#kali-mobile  下载通用版full
    + 使用文章
  + TWRP
  + magisk
  + 刷入TWRP后 进rce先双清 然后刷入MIUI11 然后刷入magisk，先开机进系统修补boot， 然后刷入nethunter 然后刷入内核
  + system分区不够 需要用多系统工具箱扩容
+ 准备买个nexus6p也整个nethunter

  + https://blog.csdn.net/qq_44709006/article/details/124122937#t6
  + https://www.bilibili.com/video/BV1x24y1n7Jm/
  + https://www.52pojie.cn/thread-1847814-1-1.html
  + 搞好了，扩容system分区重新刷system.img还是会重置大小
  + 索性直接安装23年4月版本成功了
+ 今天晚上一面通过了，准备过几天的厂商面，希望今年蓝中1.8/8能安安稳稳的，希望不要冲突

## 第二十一周（2024.5.13-2024.5.19）

> 厂商面、iscc第三周、iscc wp

+ 被长亭鸽了两天了，真生气，真不想磨性子，护网准备面试真是苦恼，两三天没去健身房了，废了妈的
+ iscc放题了，有概率拿一等奖，wp写完就完事了
+ ok呀，长亭漏面推迟到下周了，寄了
+ 想研究360src了 主要是软件层面的
  + 有人有一个bypass startup的方法 公开在自己博客 被别人交了src赚了5k
  + 作者本人本来可以赚1w+的
+ 多看点国外文章吧https://medium.com/mitre-attack
  + https://www.shentoushi.top/att/
+ https://idiotc4t.com/

## 第二十二周（2024.5.20-2024.5.26）

> 数字中国半决赛、厂商面、iscc wp、举办比赛

+ 决赛总第20，优胜奖，差4名拿钱
+ CT
  + 总结
    问护网经验 问工作内容 担当角色
    问内网流程 和经验
    问内存马利用 原理（答得不好）
    问你其他优势（觉得自己什么地方厉害讲什么，护网中有什么成果都讲出来）
    问上机应急流程
    问工作地点 是否可以华南
    问hw前置工作是否可以担任
  + 感觉有戏，都问我后面两个问题了
+ iscc快结束了，还差8个wp
+ 举办学校信安比赛
+ iscc结束了
  + 排300几 应该可以拿一等
  + 擂台摆烂 不交wp了
+ 学校赛题也出完了，等后面开始了，开始之前还要培训
+ 鬼故事 六级还有不到20天考 已经一周没背单词了
+ https://www.52pojie.cn/thread-1926574-1-1.html
  + 基于Electron的CrackMe
+ 无限debugger绕过
  + 修改断点为false
  + 文件覆盖
    + 修改代码
  + setInterval=function(){} 置空
  + hook constructor
  + 用火狐

## 第二十三周（2024.5.27-2024.6.2）

> 免杀、英语、写BOF、RUST免杀、C#免杀

+ https://www.kancloud.cn/wizardforcel/gdb-tips-100
  + gdb技巧
+ 突然发现自己VPS的ip被标记了
  + 只是历史解析的网站标题有我的个人网站标题
+ 我的免费域名也被标记了
  + 标记到了CS估计
+ 换ip需要3美刀，还是算了吧
  + 有CDN就是神 不怕被溯源
+ https://xz.aliyun.com/t/13687
  + syscall学习
+ **长亭蓝中过了！！！**
+ https://github.com/b4rth0v5k1/BOF_Beginner
  + bof
+ https://github.com/es3n1n/no-defender
  + wd
+ https://github.com/coldpon/ring3-hidden
+ https://github.com/HackerCalico/No_X_Memory_ShellCodeLoader
+ https://github.com/xiao-zhu-zhu/RustBypassMap
  + 好项目 学！
+ RUST写完了 不错！
+ https://mp.weixin.qq.com/s/48-3w6yrPWqT05T52ngNZg
  + 重新认识CS
+ https://github.com/timwhitez/Doge-Gabh
  + 门集成
+ https://xz.aliyun.com/t/14018
  + edr c# bypass

## 第二十四周（2024.6.3-2024.6.9）

> 免杀、准备国护、举办校赛、六级

+ 最紧张的一周，国赛和护网千万不要冲突
+ 收到消息国护要到七月了
+ 校赛举办完了
+ 收到消息国赛要到七月底了
+ https://github.com/Chemiculs/qengine
  + c控制流混淆库
+ https://forum.butian.net/share/3035
  + fuzz案例
+ 好，有个项目被鸽了，准备六级吧
+ 好，陷入消费主义陷阱，买了个没有大陆优化的VPS，还续费了自己之前的VPS共花费：150RMB
  + 用了1panel 换了CS4.9
+ 弄了下分离加载的东西
+ 弄了下线程注入的东西

## 第二十五周（2024.6.10-2024.6.16）

> 六级、省护

+ 端午安康
  + 吃了健身搭子给的三个甜粽子
+ https://www.vpss.cc/381.html
  + mimikatz bypass
+ https://mp.weixin.qq.com/s/TqHhggmud6Bsna0RGy22ag
  + lsass转储
+ https://blog.csdn.net/zhangkexin3/article/details/135865120
  + lsass转储 reg
+ 才发现续费两年的VPS每个月有1T流量，不买机场了以后
  + https://jiasupanda.com/vmess-vultr
  + https://jiasupanda.com/vultr-trojan#yi_jian_bu_shu_fu_wu_qi_duan
  + 不弄了 怕VPS被墙
+ https://fluxsec.red/etw-patching-rust
+ https://www.sektor7.net/
+ https://space.bilibili.com/612529727
  + 红队开发
+ https://space.bilibili.com/327331239
  + sektor7

## 第二十六周（2024.6.17-2024.6.23）

> 省护

+ 打了五天省护，结果做的工具没怎么派上用场
+ 最终结果是11/34，感觉自己是弱口令战神
+ 饭很好吃，住宿的地方电影很好看，我的队友很可爱

## 第二十七周（2024.6.24-2024.6.30）

> 重装电脑，扩容电脑

+ 装了原版win10，扩容2t硬盘
+ https://9bie.org/index.php/
  + 大佬博客
+ ~~https://9bie.org/index.php/archives/865/~~
  + ~~准备实践一下 自建验证码模型~~
  + 还是花钱找api把...
+ https://9bie.org/index.php/archives/786/
  + 有意思的win10输入法词频取证

## 第二十八周（2024.7.1-2024.7.7）

> 贵州项目，金砖

+ 金砖也是晋级了
  + 体验究极差的一个比赛（米好sima）
+ 究极难忘的一次项目
+ 涉密就不说了
+ 喜欢贵州！
+ 对了这几天电脑还被上马了，还好几分钟就排查隔离了

## 第二十八周（2024.7.8-2024.7.14）

> 毕业季

+ https://github.com/veo/vshell
+ https://mp.weixin.qq.com/s/b0mphQG-nny0X087JsjsKQ
  + fdx佬的文章
+ https://mp.weixin.qq.com/s/cl0rGIYKugMeE5hUrXPM_g
  + 回顾一下shellcodeload
+ 最近真的好摆烂

## 第二十八周（2024.7.15-2024.7.21）

> 暑假集训，免杀开发

+ 跟着fdx佬弄了下patch bypass的内容 决定将其武器化
  + https://mp.weixin.qq.com/s/b0mphQG-nny0X087JsjsKQ
  + 基本上实现了 名为BinarySpy
+ https://mp.weixin.qq.com/s/htc8ZTbQ23kq3TEMlkqSfA
  + 昔日的前辈也是干上黑产了
+ 还写了一个资源替换的小工具
  + https://github.com/yj94/ResSpy
+ 这周的免杀
  + auto patch
  + 捆绑 释放 自删除
  + 无线程注入
    + 无法过360核晶
+ 国护好像要开始了？22号
  + 前几天还被ct催平台考试
+ https://www.henry-blog.life/henry-blog
  + 大佬博客
+ https://github.com/HACK-THE-WORLD/IDAPluginList

## 第二十九周（2024.7.22-2024.7.28）

> 煎熬的一周

+ 有的人已经入场了 有的人还没通知
+ 学习一下别人的https://www.binaryai.cn/
+ https://www.geekby.site/
  + 大佬博客
+ 马上入场了！
  + 给我买了保险，还没入，我服了
+ https://oblivions-research.gitbook.io/journal
  + evasion
+ 上周水了篇文章 还没审核！先知你给我快点上班

## 第三十周（2024.7.29-2024.8.4）
