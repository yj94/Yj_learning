#include <Windows.h>
#include <iostream>
void MsgShellcode() {
	/*
	kernel32.dll��Windows����ϵͳ�ĺ������֮һ����������ϵͳ���ڴ�������ݵ�������������ȡ�

	user32.dll��Windows�û��������Ӧ�ó���ӿڣ���Ҫ���ڰ���Windows���������û���������ԣ��紴�����ںͷ�����Ϣ��

	ntdll.dll��NT����ϵͳ���ں˼�����������Ҫ�ṩ��һЩ�����Ĳ���ϵͳ��������̺��̹߳����ڴ�����Լ��ļ�ϵͳ���ʵȡ�

	TEB �̻߳���ģ��
	PEB ���̻���ģ��
	SEH Winodws�쳣�������
	NtCurrentTeb()��ȡTEBָ��
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