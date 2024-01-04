#pragma once
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include "MyStd.h"
// #pragma comment (lib, "d2d1.lib")
// #pragma comment (lib, "dwrite.lib")

class MyDxWrite
{
public:
	ID2D1RenderTarget* m_pRenderTarget = nullptr;
	ID2D1Factory* m_pD2DFactory = nullptr;
	ID2D1SolidColorBrush* m_pDefaultBrush = nullptr;
	IDWriteFactory* m_pWriteFactory = nullptr;
	IDWriteTextFormat* m_pTFGungseo30 = nullptr;
	IDWriteTextFormat* m_pTFGothic20 = nullptr;
	IDWriteTextFormat* m_pTFGothic15 = nullptr;

public:
	static MyDxWrite& Get()
	{
		static MyDxWrite dw;
		return dw;
	}

public:
	void DrawGungseo30(
		float x,
		float y,
		std::wstring msg,
		D2D1::ColorF color = D2D1::ColorF(0, 0, 0, 1));
	void DrawGothic20(
		float x,
		float y,
		std::wstring msg,
		D2D1::ColorF color = D2D1::ColorF(0, 0, 0, 1));
	void DrawGothic15(
		float x,
		float y,
		std::wstring msg,
		D2D1::ColorF color = D2D1::ColorF(0, 0, 0, 1));

public:
	bool Init(IDXGISurface* dxgiSurface);
	bool Frame();
	// 출력 테스트용 함수
	bool Render();
	bool Release();

private:
	MyDxWrite() {}

public:
	~MyDxWrite()
	{
		Release();
	}
};

