# Blue Team

## 维持相关

+ 计划任务
  + /var/spool/cron/
  + /etc/crontab
  + /etc/cron.xxx
    + crontab -u root -l 列出root的计划任务
    + crontab -u root -r 删除root的计划任务
    + crontab -u root -e 编辑root的计划任务
+ SUID
  + find / -user root -perm -4000 -print 2>/dev/null  查找带有SUID的二进制文件
+ SSH
  + 攻击者 ssh-keygen -t rsa 生成到~/.ssh/id_rsa.pub
    + ~/.ssh/authorized_keys 查找是否有非法密钥
  + ln -sf /usr/sbin/sshd /usr/local/su;/usr/local/su -oPort=12345 软连接su用户到ssh
    + ls -al查看是否link
    + ps -aux 查看进程 netstat -pant
+ 环境变量
  + export PROMPT_COMMAND="eval command" 每次执行命令同时执行
    + unset PROMPT_COMMAND
  + export HISTSIZE=0
    export HISTFILE=/dev/null 修改history
  + /etc/bash.bashrc  开机shell 全局环境变量
  + ~/.bashrc 当前用户shell环境变量
  + ~/.bash_logout 当前用户shell关闭环境变量
  + alias ls = 'ls -al'
    + which -a ls 查找命令为ls的二进制文件(找后门)
+ 痕迹
  + 时间
    + touch -r old new 将new文件的时间戳改为old
    + touch -t timestamp file 改指定时间戳
    + touch -m 只修改修改文件时间 -a 只修改访问时间
  + sed –i 's/192.168.1.3/192.168.1.4/' /var/log/apache/access.log
    + 修改前者ip为后者
    + -i修改文件
    + -i.bak 修改文件同时创建备份
  + sed -i '150,$d' .bash_history 只保留150行之前的数据
  + find ./ -cmin -30 ，30分钟内被修改过的文件
  + grep -rn "eval(" ./
  + chattr +i 不可修改权限
  + userdel -R "user"
+ 日志
  * /var/log/cron    记录了系统定时任务相关的日志
  * /var/log/cups	记录打印信息的日志
  * /var/log/dmesg	记录了系统在开机时内核自检的信息，也可以使用dmesg命令直接查看内核自检信息
  * /var/log/mailog    记录邮件信息
  * /var/log/message    记录系统重要信息的日志。这个日志文件中会记录Linux系统的绝大多数重要信息，如果系统出现问题时，首先要检查的就应该是这个日志文件
  * /var/log/btmp    记录错误登录日志，这个文件是二进制文件，不能直接vi查看，而要使用lastb命令查看
  * /var/log/lastlog	记录系统中所有用户最后一次登录时间的日志，这个文件是二进制文件，不能直接vi，而要使用lastlog命令查看
  * /var/log/wtmp	永久记录所有用户的登录、注销信息，同时记录系统的启动、重启、关机事件。同样这个文件也是一个二进制文件，不能直接vi，而需要使用last命令来查看
  * /var/log/utmp	记录当前已经登录的用户信息，这个文件会随着用户的登录和注销不断变化，只记录当前登录用户的信息。同样这个文件不能直接vi，而要使用w,who,users等命令来查询
  * /var/log/secure	记录验证和授权方面的信息，只要涉及账号和密码的程序都会记录，比如SSH登录，su切换用户，sudo授权，甚至添加用户和修改用户密码都会记录在这个日志文件中
  * /var/log/wtmp 登录进入，退出，数据交换、关机和重启纪录
  * /var/log/lastlog 文件记录用户最后登录的信息，可用 lastlog 命令来查看。
  * /var/log/secure 记录登入系统存取数据的文件，例如 pop3/ssh/telnet/ftp 等都会被记录。
  * /var/log/cron 与定时任务相关的日志信息
  * /var/log/message 系统启动后的信息和错误日志
  * /var/log/apache2/access.log apache access log
    * sed -i -e '/shell.php/d' /var/log/httpd/access.log 匹配删除包含shell.php的行
  * 
+ 进程
  + export LD_PRELOAD=/path/to/backdoor
    + 动态链接预加载的程序为后门
    + unset
+
