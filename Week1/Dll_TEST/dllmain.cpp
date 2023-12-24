// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <Windows.h>
extern "C" __declspec(dllexport) VOID ShowMessage(const char* message);
extern "C" __declspec(dllexport) INT main();


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        OutputDebugString(L"DLL Inject Sucess");
        main();
        MessageBox(NULL, L"dll ATTACH sucess", L"sucess", MB_OK);
        break;//加载DLL时运行d
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

LRESULT CALLBACK KeyboardProc(
    int code,
    WPARAM wParam,
    LPARAM lParam
)
{
    if (code == HC_ACTION)
    {
        if (wParam == VK_INSERT && (lParam & (1 << 30)))
            MessageBoxA(NULL, "您按下了INSERT键", "success", MB_OK);
    }

    return  CallNextHookEx(0, code, wParam, lParam);

}
extern "C" _declspec(dllexport)  HOOKPROC getDllPoint(void)
{
    return KeyboardProc;
}
void ShowMessage(const char* message)
{
    MessageBoxA(NULL, message, "DLL Message", MB_OK);
}
int main() {
    DWORD processId;
    HANDLE hProcess, hCurrentProcess;
    MessageBoxA(NULL, "调用dll main函数成功", "success", MB_OK);
    char ss[10] = "Hacked";
    // 获取当前进程ID
    processId = GetCurrentProcessId();

    // 打开当前进程
    hCurrentProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, processId);
    if (hCurrentProcess == NULL)
    {
        MessageBoxA(NULL, "无法打开当前进程", "ERROR", MB_OK);
        return 1;
    }
    WriteProcessMemory(hCurrentProcess,(void *)0x7FF6BE8AE000,&ss,sizeof(ss),NULL);

}