#include "MyWindow.h"

// ���� ����
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

// ������ �������� Ŭ���� ���
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

// ������ �ʱ�ȭ �� ����
BOOL MyWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    // Ŭ���̾�Ʈ ���� ����
    RECT rt = { 0, 0, 1600, 900 };
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;

    // ������ Ŭ���̾�Ʈ ������ �°� â ũ�⸦ ����Ͽ� ��ȯ�ϴ� �Լ� (rt�� �޾Ƽ� rt�� ��ȯ)
    AdjustWindowRect(&rt, dwStyle, FALSE);

    // ������ ����.
    HWND hWnd = CreateWindowW(
        L"Lee's Window", L"Lee's Project",
        dwStyle, 100, 100,
        rt.right-rt.left, rt.bottom-rt.top,
        nullptr, nullptr, hInstance, nullptr);
    if (!hWnd)
    {
        return FALSE;
    }

    // ���� �� ��� ������ �ڵ� ����
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

    // 1) ������ �������� Ŭ���� ���
    MyRegisterClass(m_hInstance);
    // 2) ������ �ʱ�ȭ �� ����
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
        // ������ �޼��� ó�� ��ƾ
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
            {
                break;
            }
        }
        // ���� ���� ���� ����
        else
        {
            // tick �� ���� �ð� ���
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
