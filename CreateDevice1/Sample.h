#pragma once
#include "MyWindows.h"
#include <d3d11.h>

struct Vertex
{
	float x;
	float y;
	Vertex() { x = 0; y = 0; };
	Vertex(float _x, float _y) { x = _x, y = _y; };

}typedef Vertex;

class Sample : public MyWindows
{
	std::list<Vertex> m_vertexList;
	std::list<int> m_indexList;

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pd3dContext = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;

public:
	bool    Init()		override;
	bool    Render()	override;
	bool    Release()	override;

public:
	bool CreateVertexBuffer();
};