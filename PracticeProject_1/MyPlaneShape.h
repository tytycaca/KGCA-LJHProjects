#pragma once
#include "MyTextureMgr.h"


struct MyVector2
{
	float x = 0;
	float y = 0;

	MyVector2() {};
	MyVector2(float x, float y) { x = 0; y = 0; }

	float LengthSquared()
	{
		return (x * x, y * y);
	}
	float Length()
	{
		return sqrt(LengthSquared());
	}

	MyVector2 Normal()
	{
		float fLength = Length();
		float invertLength = 1.0f / fLength;
		return MyVector2(x * invertLength, y * invertLength);
	}

	void Normalized()
	{
		float InvertLength = 1.0 / Length();
		x *= InvertLength;
		y *= InvertLength;
	}

	MyVector2& operator+=(const MyVector2& mV2)
	{
		x += mV2.x;
		y += mV2.y;
		return *this;
	}
	MyVector2& operator-=(const MyVector2& mV2)
	{
		x -= mV2.x;
		y -= mV2.y;
		return *this;
	}

	// 함수 뒤에 붙는 const 의 의미: 해당 멤버 함수 안에 있는 모든 멤버 변수를 상수화 시킨다
	MyVector2 operator+(const float bias) const
	{
		return MyVector2(x + bias, y + bias);
	}
	MyVector2 operator-(const float bias) const
	{
		return MyVector2(x - bias, y - bias);
	}
	MyVector2 operator*(const float scale) const
	{
		return MyVector2(x * scale, y * scale);
	}
	MyVector2 operator/(const float scale) const
	{
		return MyVector2(x / scale, y / scale);
	}

	MyVector2 operator+(const MyVector2 mV2) const
	{
		return MyVector2(x + mV2.x, y + mV2.y);
	}
	MyVector2 operator-(const MyVector2 mV2) const
	{
		return MyVector2(x - mV2.x, y - mV2.y);
	}
	MyVector2 operator*(const MyVector2 mV2) const
	{
		return MyVector2(x * mV2.x, y * mV2.y);
	}
	MyVector2 operator/(const MyVector2 mV2) const
	{
		return MyVector2(x / mV2.x, y / mV2.y);
	}

	bool operator==(const MyVector2& mV2) const
	{
		if (fabs(x - mV2.x) < 0.001f && fabs(y - mV2.y) < 0.001f)
			return true;
		return false;
	}

	bool operator!=(const MyVector2& mV2) const
	{
		return !(*this == mV2);
	}
};

struct MyVector3
{
	float x;
	float y;
	float z;
	MyVector3() { x = 0; y = 0; z = 0; }
	MyVector3(float _x, float _y, float _z = 0.0f) { x = _x; y = _y; z = _z; }
};

struct MyVector4
{
	float x;
	float y;
	float z;
	float w;
	MyVector4() { x = 0; y = 0; z = 0; w = 0; }
	MyVector4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
};

struct MyVertex
{
	MyVector3 pos;
	MyVector4 color;
	MyVector2 uv;
	
	MyVertex() {}
	MyVertex(MyVector3 p, MyVector4 c, MyVector2 u) { pos = p; color = c; u = uv; }
};


class MyPlaneShape 
{
public:
	MyPlaneShape()
	{
		// 객체 생성할때 바로 초기화
		Init();
	}

public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pd3dContext = nullptr;

	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pIndexBuffer = nullptr;
	std::vector<MyVertex> m_VertexList;
	std::vector<DWORD> m_IndexList;

	W_STR m_csDefaultVSFileName;
	C_STR m_csDefaultVSEntryName;
	ID3DBlob* m_pVertexShaderByteCode = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	W_STR m_csDefaultPSFileName;
	C_STR m_csDefaultPSEntryName;
	ID3DBlob* m_pPixelShaderByteCode = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11InputLayout* m_pVertexlayout = nullptr;

	MyTexture* m_pTexture = nullptr;
	std::vector<MyTexture*> m_pTextureArr;
	W_STR m_csName;

public:
	virtual bool CreateVertexBuffer();
	virtual bool CreateIndexBuffer();

	virtual bool CreateVertexShader();
	virtual bool CreatePixelShader();
	virtual bool CreateInputLayout();

	virtual bool LoadTexture(W_STR texFileName);
	virtual bool LoadTexture(T_STR_VECTOR texFileArray);

	// Plane 생성
	virtual bool Create(W_STR name, W_STR texFileName);
	virtual bool Create(W_STR name, T_STR_VECTOR texFileArray);

public:
	virtual bool Init();
	virtual bool Frame();
	// 렌더값 설정하는 부분 (SetShader, SetInputLayout, SetIndexBuffer 등등)
	virtual bool PreRender();
	// 실제로 DeviceContext 의 DrawIndexed 함수를 통해 렌더하는 부분
	virtual bool PostRender();
	virtual bool Render();
	virtual bool Release();
};

