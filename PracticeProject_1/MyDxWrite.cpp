#include "MyDxWrite.h"

bool MyDxWrite::Init(IDXGISurface* dxgiSurface)
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_pD2DFactory);
	if (FAILED(hr))
	{
		return false;
	}
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pWriteFactory);
	if (FAILED(hr))
	{
		return false;
	}

	hr = m_pWriteFactory->CreateTextFormat(
		L"궁서",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		30,
		L"ko-kr",
		&m_pTFGungseo30);
	if (FAILED(hr))
	{
		return false;
	}

	hr = m_pWriteFactory->CreateTextFormat(
		L"고딕",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20,
		L"ko-kr",
		&m_pTFGothic20);
	if (FAILED(hr))
	{
		return false;
	}

	hr = m_pWriteFactory->CreateTextFormat(
		L"고딕",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15,
		L"ko-kr",
		&m_pTFGothic15);
	if (FAILED(hr))
	{
		return false;
	}

	FLOAT x, y;

	UINT dpi = GetDpiForWindow(g_hWnd);
	D2D1_RENDER_TARGET_PROPERTIES rtp;
	rtp.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	rtp.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	rtp.pixelFormat.format = DXGI_FORMAT_UNKNOWN;
	rtp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
	rtp.dpiX = dpi;
	rtp.dpiY = dpi;
	rtp.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	hr = m_pD2DFactory->CreateDxgiSurfaceRenderTarget(
		dxgiSurface,
		&rtp,
		&m_pRenderTarget);

	D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Black);
	hr = m_pRenderTarget->CreateSolidColorBrush(
		color,
		&m_pDefaultBrush);

	return true;
}

bool MyDxWrite::Frame()
{
	return true;
}

// 출력 테스트용 함수
bool MyDxWrite::Render()
{
	if (m_pRenderTarget == nullptr) return true;
	std::wstring msg = L"텍스트 출력 테스트";
	m_pRenderTarget->BeginDraw();
	D2D1_RECT_F rtf = { 0.0f, 0.0f, 1600.0f, 900.0f };
	D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Black);
	m_pDefaultBrush->SetColor(color);
	m_pRenderTarget->DrawText(msg.c_str(), msg.size(), m_pTFGothic20, rtf, m_pDefaultBrush);
	m_pRenderTarget->EndDraw();

	return true;
}

void MyDxWrite::DrawGungseo30(float x, float y, std::wstring msg, D2D1::ColorF color)
{
	m_pRenderTarget->BeginDraw();
	D2D1_RECT_F rtf = { x, y, 1600.0f, 900.0f };
	m_pDefaultBrush->SetColor(color);
	m_pRenderTarget->DrawText(msg.c_str(), msg.size(), m_pTFGungseo30, rtf, m_pDefaultBrush);
	m_pRenderTarget->EndDraw();
}

void MyDxWrite::DrawGothic20(float x, float y, std::wstring msg, D2D1::ColorF color)
{
	m_pRenderTarget->BeginDraw();
	D2D1_RECT_F rtf = { x, y, 1600.0f, 900.0f };
	m_pDefaultBrush->SetColor(color);
	m_pRenderTarget->DrawText(msg.c_str(), msg.size(), m_pTFGothic20, rtf, m_pDefaultBrush);
	m_pRenderTarget->EndDraw();
}

void MyDxWrite::DrawGothic15(float x, float y, std::wstring msg, D2D1::ColorF color)
{
	m_pRenderTarget->BeginDraw();
	D2D1_RECT_F rtf = { x, y, 1600.0f, 900.0f };
	m_pDefaultBrush->SetColor(color);
	m_pRenderTarget->DrawText(msg.c_str(), msg.size(), m_pTFGothic15, rtf, m_pDefaultBrush);
	m_pRenderTarget->EndDraw();
}

bool MyDxWrite::Release()
{
	if (m_pD2DFactory)
	{
		m_pD2DFactory->Release();
		m_pD2DFactory = nullptr;
	}
	if (m_pDefaultBrush)
	{
		m_pDefaultBrush->Release();
		m_pDefaultBrush = nullptr;
	}
	if (m_pWriteFactory)
	{
		m_pWriteFactory->Release();
		m_pWriteFactory = nullptr;
	}
	if (m_pTFGungseo30)
	{
		m_pTFGungseo30->Release();
		m_pTFGungseo30 = nullptr;
	}
	if (m_pTFGothic20)
	{
		m_pTFGothic20->Release();
		m_pTFGothic20 = nullptr;
	}
	if (m_pRenderTarget)
	{
		m_pRenderTarget->Release();
		m_pRenderTarget = nullptr;
	}

	return true;
}