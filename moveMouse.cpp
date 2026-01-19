#include <iostream>
#include <Windows.h>
#include "project.h"

void CenterMouse()
{
    const int x = GetSystemMetrics(SM_CXSCREEN) / 2;
    const int y = GetSystemMetrics(SM_CYSCREEN) / 2;

    SetCursorPos(x, y);

    printLog(level_INFO, "Move the mouse to the center of the screen.");
}

void DrawCrosshair()
{
    int x = GetSystemMetrics(SM_CXSCREEN) / 2;
    int y = GetSystemMetrics(SM_CYSCREEN) / 2;

    HDC hdc = GetDC(NULL);
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    SelectObject(hdc, hPen);
    MoveToEx(hdc, x - 20, y, NULL);
    LineTo(hdc, x + 20, y);
    MoveToEx(hdc, x, y - 20, NULL);
    LineTo(hdc, x, y + 20);

    DeleteObject(hPen);
    ReleaseDC(NULL, hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    printLog(level_INFO, "Draw crosshairs on the screen.");

    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT rect;
        GetClientRect(hwnd, &rect);
        int x = (rect.right - rect.left) / 2;
        int y = (rect.bottom - rect.top) / 2;

        // 创建一个红色画笔
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        SelectObject(hdc, hPen);

        // 画水平线
        MoveToEx(hdc, x - 20, y, NULL);
        LineTo(hdc, x + 20, y);

        // 画垂直线
        MoveToEx(hdc, x, y - 20, NULL);
        LineTo(hdc, x, y + 20);

        // 清理资源
        DeleteObject(hPen);
        EndPaint(hwnd, &ps); // 正确释放
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    const wchar_t CLASS_NAME[] = L"CrosshairWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0)); // 背景刷成黑色

    RegisterClass(&wc);

    HWND hwnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT,
        CLASS_NAME,
        L"Crosshair",
        WS_POPUP,
        0, 0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, hInstance, NULL);

    // 设置颜色键透明：黑色部分透明
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
