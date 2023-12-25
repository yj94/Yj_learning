#include <Windows.h>
#include <iostream>
void MsgShellcode() {
	/*
	kernel32.dll是Windows操作系统的核心组件之一，它控制着系统的内存管理、数据的输入输出操作等。

	user32.dll是Windows用户界面相关应用程序接口，主要用于包括Windows处理，基本用户界面等特性，如创建窗口和发送消息。

	ntdll.dll是NT操作系统的内核级驱动程序，主要提供了一些基本的操作系统服务，如进程和线程管理、内存管理以及文件系统访问等。

	TEB 线程环境模块
	PEB 进程环境模块
	SEH Winodws异常处理机制
	NtCurrentTeb()获取TEB指针
	*/
	LoadLibraryA("user32.dll");
	__asm {
		//hello yj
		push 0x6A79206F;
		push 0x6C6C6568;
		mov eax, esp;
		xor edx, edx;
		push edx;
		push edx;
		push eax;
		push edx;
		mov ebx, 0x75F00A50;//MessageBoxA() addr
		call ebx;
		mov ecx, 0x7B5D6CE0;//exit() addr
		push edx;
		call ecx;
	}
}
void xor_encrypt(unsigned char* a,int b) {
	unsigned int xor_key = 0x23;
	unsigned int tmp;
	for (int i = 0; i < b; i++) {
		if (a[i] == 0) {
			break;
		}
		tmp= a[i] ^ xor_key;
		printf("\\x%x", tmp);
	}
}
int main() {
	//MsgShellcode();
	char pos[] = "here is";
	//unsigned char shellcode[] = "\x68\x6F\x20\x79\x6A\x68\x68\x65\x6C\x6C\x8B\xC4\x33\xD2\x52\x52\x50\x52\xBB\x50\x0A\xF0\x75\xFF\xD3\xB9\xE0\x6C\x5D\x7B\x52\xFF\xD1";
	//int shellcode_len = sizeof(shellcode);
	//xor_encrypt(shellcode, shellcode_len);
	//exit(0);
}