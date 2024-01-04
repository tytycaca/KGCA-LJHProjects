#include "MyMain.h"

bool MyMain::Init()
{
    m_Player = std::make_shared<MyPlayerObj>();
    m_Player->m_pd3dDevice = m_pd3dDevice;
    m_Player->m_pd3dContext = m_pd3dContext;
    m_Player->m_rtClientWindow = m_rtClientWindow;

    MyInitSet info = { L"Player", L"../../data/resources/skyblue.png",
                    {800.0f, 450.0f },
                    {91.0f,1.0f},
                    {40.0f, 60.0f},300.0f };
    if (!m_Player->Create(info, L"../../data/resources/player.png"))
    {
        return false;
    }

    return true;
}

bool MyMain::Frame()
{
    m_Player->Frame();

    return true;
}

bool MyMain::Render()
{
    m_Player->Render();

    return true;
}

bool MyMain::Release()
{
    m_Player->Release();

    return true;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    MyMain myMain;
    myMain.SetWindow(hInstance, nCmdShow);
    myMain.Run();
    return 0;
}