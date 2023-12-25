// Win_MSG.cpp: 定义应用程序的入口点。
//

#include "Win_MSG.h"
#define IDC_BUTTON1  1002
using namespace std;
int closeNotepad() {
	HWND hNoteWnd = FindWindow(NULL, "无标题 - 记事本");
	if (hNoteWnd == NULL)
	{
		return -1;
	}
	DWORD dwNotePid = 0;
	GetWindowThreadProcessId(hNoteWnd, &dwNotePid);
	if (dwNotePid == 0)
	{
		return -1;
	}

	HANDLE hNoteHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwNotePid);
	if (hNoteHandle == NULL)
	{
		return -1;
	}
	BOOL bRet = TerminateProcess(hNoteHandle, 0);

	if (bRet == TRUE)
	{
		MessageBox(NULL, "结束进程成功", NULL, MB_OK);
	}
	CloseHandle(hNoteHandle);
}
void openDebugPri() {
	HANDLE hToken = NULL;

	BOOL bRet = OpenProcessToken(GetCurrentProcess(),
		TOKEN_ALL_ACCESS, &hToken);

	if (bRet == TRUE)
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL,
			SE_DEBUG_NAME,
			&tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken,
			FALSE, &tp, sizeof(tp),
			NULL, NULL);

		CloseHandle(hToken);
	}
}
DWORD WINAPI ThreadProc(LPVOID lpParam)
{	
	for (int i = 0; i < 10; i++) {
		printf("ThreadProc %d \r\n",i);
	}
	
	return 0;

}
typedef void (*ShowMessageFunc)(const char*);
typedef int (*dllmain)();
void dllFuncs() {//dll编程测试
	HINSTANCE hDll;
	ShowMessageFunc showMessage;

	hDll = LoadLibrary("test.dll");
	if (hDll != NULL)
	{
		showMessage = (ShowMessageFunc)GetProcAddress(hDll, "ShowMessage");
		dllmain dllmainFunc = (dllmain)GetProcAddress(hDll, "main");
		if (showMessage != NULL)
		{
			const char* message = "dll测试成功";
			showMessage(message);
		}
		else
		{
			printf("从dll中调用show函数失败\n");
		}
		if (dllmainFunc != NULL)
		{
			dllmainFunc();
		}
		else
		{
			printf("从dll中调用main函数失败\n");
		}
		FreeLibrary(hDll);
	}
	else
	{
		printf("加载dll失败\n");
	}
}
int main()
{
	/* 设置调试权限
	HANDLE hToken = NULL;

	BOOL bRet = OpenProcessToken(GetCurrentProcess(),
		TOKEN_ALL_ACCESS, &hToken);

	if (bRet == TRUE)
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL,
			SE_DEBUG_NAME,
			&tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken,
			FALSE, &tp, sizeof(tp),
			NULL, NULL);

		CloseHandle(hToken);
	}
	*/
	/* 线程创建
	HANDLE hThread = CreateThread(NULL,
		0,
		ThreadProc,
		NULL,
		0,
		NULL);
	for (int i = 0; i < 10; i++) {
		printf("main %d \r\n", i);
	}
	WaitForSingleObject(hThread, 3000);
	CloseHandle(hThread);

	*/
	
	system("pause");
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		return 0;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 处理按钮单击事件
		if (wmId == IDC_BUTTON1)
		{
			MessageBox(hwnd, TEXT("Hello, world!"), TEXT("提示"), MB_OK);
		}
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const char* CLASS_NAME = "MyWindowClass";
	const char* WINDOW_TITLE = "My Window";
	const int WIDTH = 300;
	const int HEIGHT = 200;
	const int IDC_BUTTON = 1;

	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = CLASS_NAME;

	if (!RegisterClass(&wc))
	{
		std::cerr << "注册窗口类失败！" << std::endl;
		return 1;
	}

	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
		NULL, NULL, hInstance, NULL);

	if (!hwnd)
	{
		std::cerr << "创建窗口失败！" << std::endl;
		return 1;
	}

	// 创建按钮
	const char* BUTTON_TEXT = "弹出消息框";
	int x = (WIDTH - 80) / 2;
	int y = (HEIGHT - 30) / 2;
	HWND hwndButton = CreateWindowEx(
		0,
		"BUTTON",
		BUTTON_TEXT,
		WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		x, y, 80, 30,
		hwnd, (HMENU)IDC_BUTTON, hInstance, NULL);

	if (!hwndButton)
	{
		std::cerr << "创建按钮失败！" << std::endl;
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}