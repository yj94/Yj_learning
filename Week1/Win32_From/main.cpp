// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include "header.h"
// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Win32_From Test Inject");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;
    openDebugPri();
    //refInject(); ������
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("ע�ᴰ����ʧ��"),
            (NULL),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 200,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    HWND hBtnWnd1 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("����"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        30, 30, 100, 30, hWnd, (HMENU)1002, hInstance, 0);
    HWND hBtnWnd2 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("��������dll"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        60, 60, 100, 30, hWnd, (HMENU)1003, hInstance, 0);
    HWND hBtnWnd3 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("ֱ��ע��dll"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        90, 90, 100, 30, hWnd, (HMENU)1004, hInstance, 0);
    HWND hBtnWnd4 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("Զ��ע��dll"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        120, 120, 100, 30, hWnd, (HMENU)1005, hInstance, 0);

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("���ô��ڴ�������ʧ��"),
            (NULL),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
char s[10] = "normal";
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, YJ!");

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        // Here your application is laid out.
        // For this introduction, we just print out "Hello, Windows desktop!"
        // in the top left corner.
        TextOut(hdc,
            5, 5,
            greeting, _tcslen(greeting));
        // End application-specific layout section.

        EndPaint(hWnd, &ps);
        break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        // ������ť����¼�
        char wmidstr = char(wmId);
        switch (wmId) {
        case 1002:
            MessageBoxA(NULL, "��ť������ˣ�", ("��ʾ%s", s), MB_ICONINFORMATION);
            break;
        case 1003:
            MessageBoxA(NULL, "��������dll", ("FUNC", s), MB_ICONINFORMATION);
            dllFuncs();
            break;
        case 1004:
            MessageBoxA(NULL, "ֱ��ע��dll", ("FUNC", s), MB_ICONINFORMATION);
            TestDllInject();
            break;
        case 1005:
            MessageBoxA(NULL, "Զ��ע��dll", ("FUNC", s), MB_ICONINFORMATION);
            RemoteDllInject();
            break;
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}