////////////////////////
// 기능 구현 및 테스트 //
////////////////////////
#include "MyCore.h"
#include "MyDXObject.h"

class Sample : public MyCore
{
	MyDXObject objScreen; // 삼각형
	MyDXObject objNDC;

public:
	void Init() override
	{
		// 화면좌표계
		// 0,0			~		800,0



		// 0,600		~		800,600
		objScreen.m_vList.resize(6);
		objScreen.m_vList[0].v = MY_Math::FVector2(-1.0f, 1.0f);
		objScreen.m_vList[1].v = MY_Math::FVector2(1.0f, 1.0f);
		objScreen.m_vList[2].v = MY_Math::FVector2(1.0f, -1.0f);

		objScreen.m_vList[3].v = MY_Math::FVector2(-1.0f, +1.0f);
		objScreen.m_vList[4].v = MY_Math::FVector2(1.0f, -1.0f);
		objScreen.m_vList[5].v = MY_Math::FVector2(-1.0f, -1.0f);

		//objScreen.m_vList[0].v = MY_Math::FVector2(0.0f, 0.0f);
		//objScreen.m_vList[1].v = MY_Math::FVector2(800, 0.0f);
		//objScreen.m_vList[2].v = MY_Math::FVector2(800, 600.0f);
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

		// 정규화된 장치 좌표계(NDC): 직각좌표계 사용
		// 어떤 좌표계를 사용하든지 관계없이
		// 최종적으로는 NDC 범위로 되어야 화면에 렌더링된다.
		// -1 ~ +1 범위로 제한하는 좌표계 (정규화된 장치 좌표계)
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
		m_ViewPort.TopLeftX = 0;
		m_ViewPort.TopLeftY = 0;
		m_ViewPort.Width = m_xWindowSize / 2;
		m_ViewPort.Height = m_yWindowSize / 2;
		m_pContext->RSSetViewports(1, &m_ViewPort);
		objScreen.Render(m_pContext);

		m_ViewPort.TopLeftX = m_xWindowSize / 2;
		m_ViewPort.TopLeftY = 0;
		m_pContext->RSSetViewports(1, &m_ViewPort);
		m_pContext->Draw(objScreen.m_vList.size(), 0);

		m_ViewPort.TopLeftX = 0;
		m_ViewPort.TopLeftY = m_yWindowSize / 2;
		m_pContext->RSSetViewports(1, &m_ViewPort);
		m_pContext->Draw(objScreen.m_vList.size(), 0);
	}
	void Release() override
	{
		objScreen.Release();
		objNDC.Release();
	}
};

MY_GAME_START(800, 600)