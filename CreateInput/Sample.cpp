#include "MyDevice.h"
#include "MyTimer.h"
#include "MyInput.h"

class Sample : public MyDevice
{
public:
	MyInput m_Input;
	MyTimer m_Timer;
	
public:
	virtual void GameRun() override
	{
		m_Timer.Frame();
		m_Timer.DebugTimer();

		if (m_isActive)
		{
			m_Input.Frame(m_hWnd);
			m_Input.DebugMousePos();
			m_Input.KeyTest();
		}
		else
		{
			Sleep(10);
		}

		MyDevice::GameRun();
	}
};

int WINAPI wWinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					PWSTR pCmdLine,
					int nCmdShow)
{
	Sample MyWin;

	MyWin.CreateRegisterClass(hInstance);
	if (MyWin.CreateWin(1024, 768))
	{
		// 그래픽 처리를 위한 초기화 작업
		if (MyWin.CreateDevice(MyWin.m_hWnd))
		{
			// 블럭 상태: 반환되면 프로그램이 끝남
			MyWin.WindowRun();
		}
		
		// 그래픽 처리를 위한 소멸 작업
		MyWin.DeleteDevice();
	}

	return 0;
}