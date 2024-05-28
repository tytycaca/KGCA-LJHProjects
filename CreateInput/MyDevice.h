#pragma once
#include "MyWindow.h"
#include <d3d11.h> // DirectX ���
#pragma comment (lib, "d3d11.lib")
//#include <d3d11.h> // DirectX ���
// 1�� ���: �Ӽ� -> ��Ŀ -> �Է� -> �߰����Ӽ� -> d3d11.lib �߰�
// 2�� ���: #pragma comment ( lib, "d3d11.lib" )
// �������� �� �س��� �������.
//#pragma comment (lib, "d3d11.lib")

class MyDevice : public MyWindow
{
public:
	// �������̽� ȹ�� (�Ҵ�, ����)
	ID3D11Device* g_pd3dDevice = nullptr;
	ID3D11DeviceContext* g_pContext = nullptr;
	IDXGISwapChain* g_pSwapChain = nullptr;
	ID3D11RenderTargetView* g_pRTV = nullptr;	// ȭ���� ��� �Ѹ��� ����

	bool CreateDevice(HWND hWnd);
	void DeleteDevice();

	virtual void GameRun() override;
};