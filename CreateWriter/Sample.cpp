#include "MyCore.h"
#include "MyWriterFont.h"
// ����� ���� �� �׽�Ʈ�Ѵ�.

class Sample : public MyCore
{
	MyWriterFont m_font;

public:
	// �ʱ�ȭ �۾�
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
	// �Ҹ� �۾�
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
		// �׷��� ó���� ���� �ʱ�ȭ �۾�
		if (myWin.CreateDevice(myWin.m_hWnd))
		{
			// �� ����: ��ȯ�Ǹ� ���α׷��� ����
			myWin.WindowRun();
		}
		myWin.DeleteDevice();
	}

	return 0;
}