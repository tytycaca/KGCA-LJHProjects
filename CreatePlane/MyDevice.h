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
	// �Ҵ�, ����
	ID3D11Device* m_pd3dDevice = nullptr;
	// ����, �
	ID3D11DeviceContext* m_pContext = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pRTV = nullptr;	// ȭ���� ��� �Ѹ��� ����
	D3D11_VIEWPORT m_ViewPort;

	bool CreateDevice(HWND hWnd);
	void DeleteDevice();
	void SetViewport();
};