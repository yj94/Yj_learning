# PWN

+ 技巧总结 https://www.cnblogs.com/xshhc/p/16939678.htmlz
+ 二进制资料 https://abcdxyzk.github.io/blog/cats/assembly/
+ 参考 https://www.yuque.com/hxfqg9/bin
+ ![1708946346737](image/pwn/1708946346737.png)

## 做题笔记

### Canary leak

Canary存在ebp之前 其大小取决于程序的bit 0x04 0x08

1. Payload_Leak = Padding + p64(Canary) + Padding_Ret + p64(rdi) + p64(puts_got) + p64(puts_plt) + p64(main)
2. Payload_Shell = Padding + p64(Canary) + Padding_Ret + p64(ret) + p64(rdi) + p64(binsh) + p64(system)

### glibc 2.27

+ 得知glibc2.27以后引入xmm寄存器, 记录程序状态, 会执行movaps指令, 要求rsp是按16字节对齐的, 所以如果payload这样写
  `payload = cyclic(0x20 + 8) + p64(pop_rdi_addr) + p64(binsh_addr) + p64(system_addr)`
  弹出的数据是奇数个, 本地就会报错
  但是改成偶数个pop
  `payload = cyclic(0x20 + 8) + p64(pop_rdi_addr) + p64(binsh_addr) + p64(ret_addr) + p64(system_addr)`
  就能打通本地了

### ret2syscall

+ 参考 https://www.cnblogs.com/fuxuqiannian/p/16913836.html
+ 没有sys且开启了NX
+ 32：pop,a,b,c,d,ret execve调用号 0xb写在pop,a后 其余两个寄存器覆盖0 p32(0) 最后执行int80 addr
+ 64：传参的寄存器是rdi->rsi->rdx->rcx->r8->r9 execve调用号 0x3b 最后执行syscall addr
+ ![1708929874831](image/pwn/1708929874831.png)

### UAF

+ use after free
+ 内存空间未被设置NULL的使用

### ret2csu

+ https://ctf-wiki.org/en/pwn/linux/user-mode/stackoverflow/x86/medium-rop/
+ 1.查找利用gadgets ![1709018072974](image/pwn/1709018072974.png)![1709018199735](image/pwn/1709018199735.png)
+ 2.给寄存器赋值 按照64的参数顺序![1709018264113](image/pwn/1709018264113.png)
+ 3.泄露write地址 使得程序重新运行main函数，根据libc基地址计算system函数和binsh字符串的真实地址，构造ROP链![1709018463535](image/pwn/1709018463535.png)
