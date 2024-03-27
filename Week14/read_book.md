# 读《网络安全应急响应技术实践指南》——奇安信

## 第一章

> 首先说一下这本书的来源，源自我朋友圈集赞得到的一本书，感谢承制安全！

+ 过于理论介绍 略过

## 第二章

> 相对来说比较平庸，此章节讲的是基础，我做过笔记的重复内容就不在下面体现了

+ 用户相关

  + win
    + net user 看不到$结尾的用户
    + wmic useraccount get /all
    + HKEY_LOCAL_MACHINE\SAM\SAM\Domains\Account 查看二进制文件是否一样，一样则为克隆用户
  + linux
    + cat /etc/passwd | grep /bin
    + /etc/shadow 查看是否有空口令用户
    + last 最后登录信息
    + who 当前登录信息
    + lastb 失败登录信息
+ 启动相关

  + win
    + Get-ScheduledTask | findstr "Ready" PS下执行 过滤掉准备就绪的计划任务
    + netstat -anob
  + linux
    + ls -alt /proc/pid
    + lsof -p pid
    + service --status-all
+ 配置相关

  + win
    + netsh Firewall show state 查看防火墙状态
+ 痕迹相关

  + win
  + linux
    + find / -perm 777 查找根目录下777权限的文件

## 第三章

> 介绍的都是老工具 比较传统，唯一不同的是在结尾介绍了自家的自动化分析工具，略过吧，工具上手就会的

## 第四章

> 勒索

## 第五章

> 挖矿

第六章

> 数据

## 第七章

> DoS

## 第八章

> 流量
