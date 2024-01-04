#pragma once
#include "MyTextureMgr.h"


struct MyVector2
{
	float x;
	float y;
	float Length()
	{
		return sqrt(LingthSquared());
	}
	float LingthSquared()
	{
		return (x * x, y * y);
	}
	MyVector2 Normal()
	{
		float fLength = Length();
		if (fLength <= 0.0f)
		{
			x = y = 0.0f;
			return *this;
		}
		float InvertLength = 1.0 / fLength;
		return MyVector2(x * InvertLength, y * InvertLength);
	}
	void Normalized()
	{
		float InvertLength = 1.0 / Length();
		x *= InvertLength;
		y* InvertLength;
	}
	MyVector2& operator+=(const MyVector2& V)
	{
		x += V.x;
		y += V.y;
		return *this;
	}
	MyVector2& operator-=(const MyVector2& V)
	{
		x -= V.x;
		y -= V.y;
		return *this;
	}
	MyVector2 operator+(const MyVector2& V) const
	{
		return MyVector2(x + V.x, y + V.y);
	}
	MyVector2 operator-(const MyVector2& V) const
	{
		return MyVector2(x - V.x, y - V.y);
	}
	MyVector2 operator-(float Bias) const
	{
		return MyVector2(x * Bias, y * Bias);
	}
	MyVector2 operator+(float Bias) const
	{
		return MyVector2(x + Bias, y + Bias);
	}
	MyVector2 operator*(float Scale) const
	{
		return MyVector2(x * Scale, y * Scale);
	}
	MyVector2 operator/(float Scale) const
	{
		return MyVector2(x / Scale, y / Scale);
	}
	bool operator==(const MyVector2& V) const
	{
		if (fabs(x - V.x) < 0.001f)
		{
			if (fabs(y - V.y) < 0.001f)
			{
				return true;
			}
		}
		return false;
	}
	bool operator!=(const MyVector2& V) const
	{
		return !(*this == V);
	}
	MyVector2() { x = 0; y = 0; }
	MyVector2(float _x, float _y) { x = _x; y = _y; }
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
	MyVertex(MyVector3 p, MyVector4 c, MyVector2 u) { pos = p; color = c; uv = u; }
};


class MyPlaneShape 
{
public:
	MyPlaneShape()
	{
		// ��ü �����Ҷ� �ٷ� �ʱ�ȭ
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

	RECT m_rtClientWindow;

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

	// Plane ����
	virtual bool Create(W_STR name, W_STR texFileName);
	virtual bool Create(W_STR name, T_STR_VECTOR texFileArray);

public:
	virtual bool Init();
	virtual bool Frame();
	// ������ �����ϴ� �κ� (SetShader, SetInputLayout, SetIndexBuffer ���)
	virtual bool PreRender();
	// ������ DeviceContext �� DrawIndexed �Լ��� ���� �����ϴ� �κ�
	virtual bool PostRender();
	virtual bool Render();
	virtual bool Release();
};

