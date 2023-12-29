#include "MyTextureMgr.h"

bool MyTexture::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext, std::wstring texFileName)
{
    // unique_ptr 텍스쳐 멤버변수에 make_unique 로 생성된 텍스쳐 인스턴스 할당
    m_tex = make_unique<DirectX::ScratchImage>();


    //////////////////
    // DDS 파일 로딩 //
    //////////////////
#pragma region
    // 메타데이터 생성 및 가져오기
    DirectX::TexMetadata metadata;
    HRESULT hr = DirectX::GetMetadataFromDDSFile(texFileName.c_str(), DirectX::DDS_FLAGS_NONE, metadata);
    if (SUCCEEDED(hr))
    {
        // DDS 파일 로딩
        hr = DirectX::LoadFromDDSFile(texFileName.c_str(), DirectX::DDS_FLAGS_NONE, &metadata, *m_tex);
        if (SUCCEEDED(hr))
        {
            // 셰이더 리소스 뷰에 자원 할당
            hr = DirectX::CreateShaderResourceView(pd3dDevice, m_tex->GetImages(), m_tex->GetImageCount(), metadata, &m_pTextureSRV);
            if (SUCCEEDED(hr))
                return true;
        }
    }
#pragma endregion


    //////////////////
    // TGA 파일 로딩 //
    //////////////////
#pragma region
    // 메타 데이터 가져오기
    hr = DirectX::GetMetadataFromTGAFile(texFileName.c_str(), DirectX::TGA_FLAGS_NONE, metadata);
    if (SUCCEEDED(hr))
    {
        // TGA 파일 로딩
        hr = DirectX::LoadFromTGAFile(texFileName.c_str(), DirectX::TGA_FLAGS_NONE, &metadata, *m_tex);
        if (SUCCEEDED(hr))
        {
            // 셰이더 리소스 뷰에 자원 할당
            hr = DirectX::CreateShaderResourceView(pd3dDevice, m_tex->GetImages(), m_tex->GetImageCount(), metadata, &m_pTextureSRV);
            if (SUCCEEDED(hr))
                return true;
        }
    }
#pragma endregion


    //////////////////
    // WIC 파일 로딩 //
    //////////////////
#pragma region
    // 메타 데이터 가져오기
    hr = DirectX::GetMetadataFromWICFile(texFileName.c_str(), DirectX::WIC_FLAGS_NONE, metadata);
    if (SUCCEEDED(hr))
    {
        // WIC 파일 로딩
        hr = DirectX::LoadFromWICFile(texFileName.c_str(), DirectX::WIC_FLAGS_NONE, &metadata, *m_tex);
        if (SUCCEEDED(hr))
        {
            // 셰이더 리소스 뷰에 자원 할당
            hr = DirectX::CreateShaderResourceView(pd3dDevice, m_tex->GetImages(), m_tex->GetImageCount(), metadata, &m_pTextureSRV);
            if (SUCCEEDED(hr))
                return true;
        }
    }
#pragma endregion


    //////////////////
    // HDR 파일 로딩 //
    //////////////////
#pragma region
    // 메타 데이터 가져오기
    hr = DirectX::GetMetadataFromHDRFile(texFileName.c_str(), metadata);
    if (SUCCEEDED(hr))
    {
        // HDR 파일 로딩
        hr = DirectX::LoadFromHDRFile(texFileName.c_str(), &metadata, *m_tex);
        if (SUCCEEDED(hr))
        {
            // 셰이더 리소스 뷰에 자원 할당
            hr = DirectX::CreateShaderResourceView(pd3dDevice, m_tex->GetImages(), m_tex->GetImageCount(), metadata, &m_pTextureSRV);
            if (SUCCEEDED(hr))
                return true;
        }
    }
#pragma endregion

    return false;
}

bool MyTexture::Release()
{
    if (m_pTextureSRV) m_pTextureSRV->Release();

    return true;
}

MyTexture* MyTextureMgr::Load(std::wstring loadFileName)
{
    // 텍스쳐 std::map에 원하는 텍스쳐가 이미 로드되서 존재하는 경우, filename 과 일치하는 페어를 찾아 texture 를 리턴
    auto iter = m_map.find(loadFileName);
    if (iter != m_map.end())
    {
        return iter->second.get();
    }

    // 텍스쳐 std::map 에 원하는 텍스쳐가 없는 경우, 텍스쳐 로딩 후 std::map 에 (filename, texture) 페어를 삽입 후 텍스쳐 리턴
    std::shared_ptr<MyTexture> pTex = std::make_shared<MyTexture>();
    if (pTex->Load(m_pd3dDevice, m_pd3dContext, loadFileName))
    {
        m_map.emplace(loadFileName, pTex);
        return pTex.get();  // .get(): shared_ptr 기능, 소유한 리소스의 주소를 가져옴 ※ 이거 물어볼것! 스마트 포인터에서 . 와 -> 의 작동원리
    }

    return nullptr;
}

bool MyTextureMgr::Release()
{
    // c# 의 foreach 와 비슷한 방식
    for (auto iter : m_map)
    {
        // 원소 삭제 전에 맵의 데이터인 MyTexture 를 릴리즈
        iter.second->Release();
    }
    // 맵의 모든 원소 삭제
    m_map.clear();

    return true;
}

MyTextureMgr::~MyTextureMgr()
{
    Release();
}
