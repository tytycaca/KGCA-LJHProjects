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
		// �׷��� ó���� ���� �ʱ�ȭ �۾�
		if (MyWin.CreateDevice(MyWin.m_hWnd))
		{
			// �� ����: ��ȯ�Ǹ� ���α׷��� ����
			MyWin.WindowRun();
		}
		
		// �׷��� ó���� ���� �Ҹ� �۾�
		MyWin.DeleteDevice();
	}

	return 0;
}