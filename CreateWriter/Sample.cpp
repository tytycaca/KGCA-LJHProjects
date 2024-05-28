#include "MyCore.h"
#include "MyWriterFont.h"
// 기능을 구현 및 테스트한다.

class Sample : public MyCore
{
	MyWriterFont m_font;

public:
	// 초기화 작업
	virtual void Init() override
	{
		int k = 0;
	}
	virtual void Frame() override
	{
		int k = 0;
	}
	virtual void Render() override
	{
		int k = 0;
	}
	// 소멸 작업
	virtual void Release() override
	{
		int k = 0;
	}

};

int WINAPI wWinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					PWSTR pCmdLine,
					int nCmdShow)
{
	Sample myWin;

	myWin.CreateRegisterClass(hInstance);
	if (myWin.CreateWin(1024, 768))
	{
		// 그래픽 처리를 위한 초기화 작업
		if (myWin.CreateDevice(myWin.m_hWnd))
		{
			// 블럭 상태: 반환되면 프로그램이 끝남
			myWin.WindowRun();
		}
		myWin.DeleteDevice();
	}

	return 0;
}