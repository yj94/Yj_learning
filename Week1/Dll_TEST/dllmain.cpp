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
        MessageBox(NULL, L"dll sucess", L"dll sucess", MB_OK);
        break;//加载DLL时运行d
    case DLL_THREAD_ATTACH:
        OutputDebugString(L"DLL free Sucess");
        MessageBox(NULL, L"dll free", L"dll free", MB_OK);
        break;//加载DLL时运行d
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
            MessageBoxA(NULL, "您按下了HOME键", "HOME", MB_OK);
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
    MessageBoxA(NULL, "调用dll成功", "DLL Message", MB_OK);
    int wmId = 0;
    if (wmId == 1002) {
        MessageBoxA(NULL, "按钮被劫持了！", "提示", MB_ICONINFORMATION);
    }
    return 0;
}