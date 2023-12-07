#include "MyWindows.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_SIZE:
        {
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            int k = 0;
        }break;

        case WM_CREATE: break;

        case WM_DESTROY:
             PostQuitMessage(0);// WM_QUIT
             break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

BOOL MyWindows::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    // 윈도우 생성 및 핸들 등록
    HWND hWnd = CreateWindowW(L"Lee's Project", L"Lee ji Hyuk", WS_OVERLAPPEDWINDOW,
        0, 0, 800, 600, nullptr, nullptr,
        hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    m_hWnd = hWnd;              // 멤버 핸들 변수에 생성된 핸들 저장
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

ATOM MyWindows::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    ZeroMemory(&wcex, sizeof(wcex));

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = L"Lee's Project";
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

    return RegisterClassExW(&wcex);
}

void MyWindows::SetWindow(HINSTANCE hInst, int nCmdShow)
{
    m_hInst = hInst;
    MyRegisterClass(m_hInst);       // 윈도우 레지스터 클래스 등록
    InitInstance(hInst, nCmdShow);  // 윈도우 생성
}

void MyWindows::Run()
{
    Init();
    MSG msg;
    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
            {
                break;
            }
        }
        else
        {
            Render();
        }
    }
    Release();
}

void MyWindows::ReleaseAll()
{
}