#include "MyMain.h"

bool MyMain::Init()
{
    return true;
}

bool MyMain::Frame()
{
    return true;
}

bool MyMain::Render()
{
    return true;
}

bool MyMain::Release()
{
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