#include "MyWindow.h"

// 전역 변수
HWND g_hWnd;

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

// 윈도우 레지스터 클래스 등록
ATOM MyWindow::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    ZeroMemory(&wcex, sizeof(wcex));

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = L"Lee's Window";
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    // wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

    return RegisterClassExW(&wcex);
}

// 윈도우 초기화 및 생성
BOOL MyWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    // 클라이언트 영역 정의
    RECT rt = { 0, 0, 1600, 900 };
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;

    // 정의한 클라이언트 영역에 맞게 창 크기를 계산하여 반환하는 함수 (rt로 받아서 rt로 반환)
    AdjustWindowRect(&rt, dwStyle, FALSE);

    // 윈도우 생성.
    HWND hWnd = CreateWindowW(
        L"Lee's Window", L"Lee's Project",
        dwStyle, 100, 100,
        rt.right-rt.left, rt.bottom-rt.top,
        nullptr, nullptr, hInstance, nullptr);
    if (!hWnd)
    {
        return FALSE;
    }

    // 전역 및 멤버 변수에 핸들 지정
    m_hWnd = hWnd;
    g_hWnd = hWnd;

    ::GetWindowRect(m_hWnd, &m_rtWindow);
    ::GetClientRect(m_hWnd, &m_rtClientWindow);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

void MyWindow::SetWindow(HINSTANCE hInstance, int nCmdShow)
{
    m_hInstance = hInstance;

    // 1) 윈도우 레지스터 클래스 등록
    MyRegisterClass(m_hInstance);
    // 2) 윈도우 초기화 및 생성
    InitInstance(hInstance, nCmdShow);
}

void MyWindow::Run()
{
    GameInit();

    DWORD dwElapseTime = 0;
    DWORD dwFrame100 = 1000 / 100;
    DWORD dwTickStart = timeGetTime();
    MSG   msg;

    while(1)
    {
        // 윈도우 메세지 처리 루틴
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
            {
                break;
            }
        }
        // 실제 게임 구동 루프
        else
        {
            // tick 을 통한 시간 계산
            DWORD dwTickEnd = timeGetTime();
            dwElapseTime += dwTickEnd - dwTickStart;

            if (dwElapseTime >= dwFrame100)
            {
                GameFrame();
                GameRender();
                dwElapseTime -= dwFrame100;
            }
            dwTickStart = dwTickEnd;
        }
    }
    
    GameRelease();
}

void MyWindow::ReleaseAll()
{
}
