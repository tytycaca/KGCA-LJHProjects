////////////////////////
// ��� ���� �� �׽�Ʈ //
////////////////////////
#include "MyCore.h"
#include "MyDXObject.h"
// ../../dxtk/include/ �� �⺻ ��η� �����Ѵ�. (�Ӽ�)
#include "WICTextureLoader.h"
#ifdef _DEBUG
#pragma comment(lib, "DirectXTK_D.lib")
#else
#pragma comment(lib, "DirectXTK_R.lib")
#endif

class Sample : public MyCore
{
	MyDXObject objScreen; // �ﰢ��
	MyDXObject objNDC;
	// ������ ����������(�Ƚ����̴�)�� ���� ������
	ID3D11ShaderResourceView*	m_pSRV = nullptr;
	// �ؽ�ó(�̹���) �ε� ������
	ID3D11Resource*				m_pTexture = nullptr;

public:
	void Init() override
	{
		HRESULT hr =
			DirectX::CreateWICTextureFromFile(
				m_pd3dDevice,
				L"bk.bmp",
				&m_pTexture,
				&m_pSRV);

		// ȭ����ǥ��
		// 0,0[0,0]			~		800,0[1,0]



		// 0,600[0,1]		~		800,600[1,1]
		objScreen.m_vList.resize(6);
		// �ð�������� ����Ǿ�� �Ѵ�.
		objScreen.m_vList[0].p = MY_Math::FVector2(m_rtClient.left, m_rtClient.top);
		objScreen.m_vList[1].p = MY_Math::FVector2(m_rtClient.right, m_rtClient.top);
		objScreen.m_vList[2].p = MY_Math::FVector2(m_rtClient.right, m_rtClient.bottom);
		objScreen.m_vList[0].c = MY_Math::FVector4(1, 0, 0, 1);
		objScreen.m_vList[1].c = MY_Math::FVector4(0, 1, 0, 1);
		objScreen.m_vList[2].c = MY_Math::FVector4(0, 0, 1, 1);
		objScreen.m_vList[0].t = MY_Math::FVector2(0, 0);
		objScreen.m_vList[1].t = MY_Math::FVector2(1, 0);
		objScreen.m_vList[2].t = MY_Math::FVector2(1, 1);

		objScreen.m_vList[3].p = MY_Math::FVector2(m_rtClient.right, m_rtClient.bottom);
		objScreen.m_vList[4].p = MY_Math::FVector2(m_rtClient.left, m_rtClient.bottom);
		objScreen.m_vList[5].p = MY_Math::FVector2(m_rtClient.left, m_rtClient.top);
		objScreen.m_vList[3].c = MY_Math::FVector4(1, 0, 0, 1);
		objScreen.m_vList[4].c = MY_Math::FVector4(0, 1, 0, 1);
		objScreen.m_vList[5].c = MY_Math::FVector4(0, 0, 1, 1);
		objScreen.m_vList[3].t = MY_Math::FVector2(1, 1);
		objScreen.m_vList[4].t = MY_Math::FVector2(0, 1);
		objScreen.m_vList[5].t = MY_Math::FVector2(0, 0);

		// ȭ�� ��ǥ�踦 NDC ��ǥ�� �����Ѵ�.
		for (auto& V : objScreen.m_vList)
		{
			// ȭ�� ��ǥ��
			MY_Math::FVector2 v = V.p;
			// 0 ~ 800 -> 0 ~ 1
			v.X = v.X / m_rtClient.right;
			v.Y = v.Y / m_rtClient.bottom;
			// NDC ��ǥ��
			// 0 ~ 1 -> -1 ~ +1
			V.p.X = v.X * 2.0f - 1.0f;
			V.p.Y = -(v.Y * 2.0f - 1.0f);
			// -1 ~ 1 -> 0 ~ 1
			/*v.X = v.X * 0.5f + 0.5f;
			v.Y = v.Y * 0.5f + 0.5f;*/
		}


		if (objScreen.CreateVertexBuffer(m_pd3dDevice) == false)
		{
			objScreen.Release();
			return;
		}
		if (objScreen.LoadShader(m_pd3dDevice) == false)
		{
			objScreen.Release();
			return;
		}
		if (objScreen.CreateInputLayout(m_pd3dDevice) == false)
		{
			objScreen.Release();
			return; 
		}

		// ����ȭ�� ��ġ ��ǥ��(NDC): ������ǥ�� ���
		// � ��ǥ�踦 ����ϵ��� �������
		// ���������δ� NDC ������ �Ǿ�� ȭ�鿡 �������ȴ�.
		// -1 ~ +1 ������ �����ϴ� ��ǥ�� (����ȭ�� ��ġ ��ǥ��)
		// -1,+1		~		+1,+1

		//			   0,0
		
		// -1,-1		~		+1,-1
		/*MyDXObject objNDC;
		objNDC.v[0] = MY_Math::FVector2(-1.0f,  1.0f);
		objNDC.v[1] = MY_Math::FVector2( 1.0f,  1.0f);
		objNDC.v[2] = MY_Math::FVector2( 1.0f, -1.0f);

		MY_Math::FVector2 v1(1, 1);
		MY_Math::FVector2 v2 = v1;
		MY_Math::FVector2 v3 = v1 * 10.0f;
		MY_Math::FVector2 v4;
		float fLength1 = v4.Length();
		bool bNorm = v4.isZero();
		float fLength2 = v1.Length();
		float fLength3 = v3.Length();
		MY_Math::FVector2 vNormalize = v1.Normalize();
		float fLength4 = vNormalize.Length();*/

		int k = 0;
	}
	void Render() override
	{
		/*m_ViewPort.TopLeftX = 0;
		m_ViewPort.TopLeftY = 0;
		m_ViewPort.Width = m_xWindowSize / 2;
		m_ViewPort.Height = m_yWindowSize / 2;
		m_pContext->RSSetViewports(1, &m_ViewPort);
		objScreen.Render(m_pContext);*/

		// 0�� �������� �ؽ�ó ����
		m_pContext->PSSetShaderResources(0, 1, &m_pSRV);
		objScreen.Render(m_pContext);
	}
	void Release() override
	{
		if (m_pSRV)
		{
			m_pSRV->Release();
			m_pSRV = nullptr;
		}
		if (m_pTexture)
		{
			m_pTexture->Release();
			m_pTexture = nullptr;
		}
		objScreen.Release();
		objNDC.Release();
	}
};

MY_GAME_START(800, 600)