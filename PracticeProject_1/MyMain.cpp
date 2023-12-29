#include "MyMain.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    MyWindow myWin;
    myWin.SetWindow(hInstance, nCmdShow);
    myWin.Run();
    return 0;
}