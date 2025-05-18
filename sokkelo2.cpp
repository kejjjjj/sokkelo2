// sokkelo2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "sokkelo2.h"

#include "app/app_window.hpp"
#include "imgui/imgui_impl_win32.h"
#include <D3D10.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

ATOM                MyRegisterClass(HINSTANCE hInstance);
HWND                InitInstance(HINSTANCE, int);

CMainWindow mainWindow(0, 0, 1280, 720);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     [[maybe_unused]]_In_opt_ HINSTANCE hPrevInstance,
                     [[maybe_unused]]_In_ LPWSTR    lpCmdLine,
                     [[maybe_unused]] _In_ int       nCmdShow)
{

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SOKKELO2, szWindowClass, MAX_LOADSTRING);

    if (!MyRegisterClass(hInstance))
        return FALSE;

    // Perform application initialization:
    auto hwnd = InitInstance(hInstance, nCmdShow);
    if (!hwnd) {
        return FALSE;
    }

    if (!mainWindow.CImGui::Initialize(hwnd))
        return FALSE;

    MSG msg{};

    auto bye = false;

    while (!bye) {

        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                bye = true;
        }

        if (bye || !mainWindow.Render())
            break;

    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = CMainWindow::WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOKKELO2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SOKKELO2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) {
      return 0;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return hWnd;
}
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK CMainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message) {
    case WM_SIZE:

        if (mainWindow.g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED) {
            mainWindow.CleanupRenderTarget();
            mainWindow.g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            mainWindow.CreateRenderTarget();

        }

        tagRECT rect;
        if (GetWindowRect(hWnd, &rect)) {
            const auto height = rect.bottom - rect.top;
            const auto width = rect.right - rect.left;

            mainWindow.SetSize(width, height);
        }
        break;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
