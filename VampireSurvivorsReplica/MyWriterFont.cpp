#include "MyWriterFont.h"
void MyWriterFont::Init() {

	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,&m_pd2dFactory);

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),(IUnknown**)&m_pWriteFactory);
	hr = m_pWriteFactory->CreateTextFormat(
		L"궁서",
		nullptr,
		DWRITE_FONT_WEIGHT_THIN,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		30,
		L"ko-kr", // L"en-us"
		&m_pWriteTF30);

	hr = m_pWriteFactory->CreateTextFormat(
		L"Gabriola",
		nullptr,
		DWRITE_FONT_WEIGHT_THIN,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		50,
		L"en-us",
		&m_pWriteTF50);

	hr = m_pWriteFactory->CreateTextFormat(
		L"LanaPixel",
		nullptr,
		DWRITE_FONT_WEIGHT_THIN,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		28,
		L"en-us",
		&m_pWriteTF28_LanaPixel);

	hr = m_pWriteFactory->CreateTextFormat(
		L"SourceCodePro",
		nullptr,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15,
		L"en-us",
		&m_pWriteTF15_SourceCodePro);
}
void MyWriterFont::ResetDevice(IDXGISurface* dxgiSurface)
{	
	D2D1_RENDER_TARGET_PROPERTIES rtp;
	rtp.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	rtp.pixelFormat.format= DXGI_FORMAT_UNKNOWN;
	rtp.pixelFormat.alphaMode= D2D1_ALPHA_MODE_PREMULTIPLIED;
	rtp.dpiX = 96;
	rtp.dpiY = 96;
	rtp.usage= D2D1_RENDER_TARGET_USAGE_NONE;
	rtp.minLevel= D2D1_FEATURE_LEVEL_DEFAULT;
	// 3d : 2D 연동가능한 렌더타켓 생성(D3D11_CREATE_DEVICE_BGRA_SUPPORT)
	HRESULT hr = m_pd2dFactory->CreateDxgiSurfaceRenderTarget(
		dxgiSurface,
		&rtp,
		&m_pd2dRT);

	if (FAILED(hr))
	{
		
	}
	D2D1_COLOR_F color = { 1,0,0,1 };//D2D1::ColorF::Yellow;
	hr = m_pd2dRT->CreateSolidColorBrush(
		color,
		&m_pDefaultColor);
	if (FAILED(hr))
	{

	}
	
}
void MyWriterFont::Frame() {
	int k = 0;
}
void MyWriterFont::DrawText(std::wstring msg, POINT pos)
{
	m_pd2dRT->BeginDraw();
	D2D1_RECT_F layoutRect = { pos.x,pos.y, 1280, 720 };
	m_pDefaultColor->SetColor({ 1,0,0,1 });
	m_pd2dRT->DrawText(msg.c_str(), msg.size(),
		m_pWriteTF30, &layoutRect, m_pDefaultColor);
	m_pd2dRT->EndDraw();
}
void MyWriterFont::Render() 
{
	m_pd2dRT->BeginDraw();
			// render
		std::wstring msg = L"게임아카데미!!!!";
		D2D1_RECT_F layoutRect = {0,0, 1280, 720};
		m_pDefaultColor->SetColor({ 0,0,0,1 });
		m_pd2dRT->DrawText(msg.c_str(), msg.size(), 
						   m_pWriteTF30,&layoutRect, m_pDefaultColor);
	m_pd2dRT->EndDraw();

	m_pd2dRT->BeginDraw();
		std::wstring msg1 = L"KGCA Game";
		D2D1_RECT_F layoutRect1 = { 200,200, 1280, 720 };
		m_pDefaultColor->SetColor({ 1,1,0,1 });
		m_pd2dRT->DrawText(msg1.c_str(), msg1.size(),
			m_pWriteTF50, &layoutRect, m_pDefaultColor);
	m_pd2dRT->EndDraw();
}

void MyWriterFont::RenderSysInfo(std::wstring timer, D2D1_RECT_F rect, D2D1_COLOR_F color)
{
	m_pd2dRT->BeginDraw();
	std::wstring msg = timer;
	D2D1_RECT_F layoutRect = rect;
	m_pDefaultColor->SetColor(color);
	m_pd2dRT->DrawText(msg.c_str(), msg.size(),
		m_pWriteTF15_SourceCodePro, &layoutRect, m_pDefaultColor);
	m_pd2dRT->EndDraw();
}

void MyWriterFont::RenderLevel(int lv, D2D1_RECT_F rect, D2D1_COLOR_F color)
{
	m_pd2dRT->BeginDraw();
	std::wstring msg = L"LV " + std::to_wstring(lv);
	D2D1_RECT_F layoutRect = rect;
	m_pDefaultColor->SetColor(color);
	m_pd2dRT->DrawText(msg.c_str(), msg.size(),
		m_pWriteTF28_LanaPixel, &layoutRect, m_pDefaultColor);
	m_pd2dRT->EndDraw();
}

void MyWriterFont::RenderHP(float hp, D2D1_RECT_F rect, D2D1_COLOR_F color)
{
	m_pd2dRT->BeginDraw();
	std::wstring msg = L"HP " + std::to_wstring((int)floor(hp));
	D2D1_RECT_F layoutRect = rect;
	m_pDefaultColor->SetColor(color);
	m_pd2dRT->DrawText(msg.c_str(), msg.size(),
		m_pWriteTF28_LanaPixel, &layoutRect, m_pDefaultColor);
	m_pd2dRT->EndDraw();
}

void MyWriterFont::RenderTimer(float timer, D2D1_RECT_F rect, D2D1_COLOR_F color)
{
	m_pd2dRT->BeginDraw();
	int sec10;
	sec10 = (int)timer / 10;
	if ((int)timer / 10 >= 6)
		sec10 -= 6;
	std::wstring msg = L"Time " + std::to_wstring((int)timer / 60 / 10) + std::to_wstring(((int)timer / 60 % 10)) +
						   L":" + std::to_wstring(sec10) + std::to_wstring(((int)timer % 10));
	D2D1_RECT_F layoutRect = rect;
	m_pDefaultColor->SetColor(color);
	m_pd2dRT->DrawText(msg.c_str(), msg.size(),
		m_pWriteTF28_LanaPixel, &layoutRect, m_pDefaultColor);
	m_pd2dRT->EndDraw();
}

void MyWriterFont::RenderStageNumber(int stage, D2D1_RECT_F rect, D2D1_COLOR_F color)
{
	m_pd2dRT->BeginDraw();
	std::wstring msg = L"STAGE " + std::to_wstring(stage / 10) + std::to_wstring(stage % 10);
	D2D1_RECT_F layoutRect = rect;
	m_pDefaultColor->SetColor(color);
	m_pd2dRT->DrawText(msg.c_str(), msg.size(),
		m_pWriteTF28_LanaPixel, &layoutRect, m_pDefaultColor);
	m_pd2dRT->EndDraw();
}

void MyWriterFont::Release() {
	if (m_pWriteTF15_SourceCodePro)
	{
		m_pWriteTF15_SourceCodePro->Release();
		m_pWriteTF15_SourceCodePro = nullptr;
	}

	if (m_pWriteTF28_LanaPixel)
	{
		m_pWriteTF28_LanaPixel->Release();
		m_pWriteTF28_LanaPixel = nullptr;
	}

	if (m_pWriteTF50)
	{
		m_pWriteTF50->Release();
		m_pWriteTF50 = nullptr;
	}
	if(m_pDefaultColor)
	{
		m_pDefaultColor->Release();
		m_pDefaultColor = nullptr;
	}
	if (m_pd2dFactory)
	{
		m_pd2dFactory->Release();
		m_pd2dFactory = nullptr;
	}
	if (m_pWriteTF30)
	{
		m_pWriteTF30->Release();
		m_pWriteTF30 = nullptr;
	}
	if (m_pWriteFactory)
	{
		m_pWriteFactory->Release();
		m_pWriteFactory = nullptr;
	}
	if (m_pd2dRT)
	{
		m_pd2dRT->Release();
		m_pd2dRT = nullptr;
	}
}