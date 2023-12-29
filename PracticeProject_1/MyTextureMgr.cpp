#include "MyTextureMgr.h"

bool MyTexture::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext, std::wstring texFileName)
{
    // unique_ptr �ؽ��� ��������� make_unique �� ������ �ؽ��� �ν��Ͻ� �Ҵ�
    m_tex = make_unique<DirectX::ScratchImage>();


    //////////////////
    // DDS ���� �ε� //
    //////////////////
#pragma region
    // ��Ÿ������ ���� �� ��������
    DirectX::TexMetadata metadata;
    HRESULT hr = DirectX::GetMetadataFromDDSFile(texFileName.c_str(), DirectX::DDS_FLAGS_NONE, metadata);
    if (SUCCEEDED(hr))
    {
        // DDS ���� �ε�
        hr = DirectX::LoadFromDDSFile(texFileName.c_str(), DirectX::DDS_FLAGS_NONE, &metadata, *m_tex);
        if (SUCCEEDED(hr))
        {
            // ���̴� ���ҽ� �信 �ڿ� �Ҵ�
            hr = DirectX::CreateShaderResourceView(pd3dDevice, m_tex->GetImages(), m_tex->GetImageCount(), metadata, &m_pTextureSRV);
            if (SUCCEEDED(hr))
                return true;
        }
    }
#pragma endregion


    //////////////////
    // TGA ���� �ε� //
    //////////////////
#pragma region
    // ��Ÿ ������ ��������
    hr = DirectX::GetMetadataFromTGAFile(texFileName.c_str(), DirectX::TGA_FLAGS_NONE, metadata);
    if (SUCCEEDED(hr))
    {
        // TGA ���� �ε�
        hr = DirectX::LoadFromTGAFile(texFileName.c_str(), DirectX::TGA_FLAGS_NONE, &metadata, *m_tex);
        if (SUCCEEDED(hr))
        {
            // ���̴� ���ҽ� �信 �ڿ� �Ҵ�
            hr = DirectX::CreateShaderResourceView(pd3dDevice, m_tex->GetImages(), m_tex->GetImageCount(), metadata, &m_pTextureSRV);
            if (SUCCEEDED(hr))
                return true;
        }
    }
#pragma endregion


    //////////////////
    // WIC ���� �ε� //
    //////////////////
#pragma region
    // ��Ÿ ������ ��������
    hr = DirectX::GetMetadataFromWICFile(texFileName.c_str(), DirectX::WIC_FLAGS_NONE, metadata);
    if (SUCCEEDED(hr))
    {
        // WIC ���� �ε�
        hr = DirectX::LoadFromWICFile(texFileName.c_str(), DirectX::WIC_FLAGS_NONE, &metadata, *m_tex);
        if (SUCCEEDED(hr))
        {
            // ���̴� ���ҽ� �信 �ڿ� �Ҵ�
            hr = DirectX::CreateShaderResourceView(pd3dDevice, m_tex->GetImages(), m_tex->GetImageCount(), metadata, &m_pTextureSRV);
            if (SUCCEEDED(hr))
                return true;
        }
    }
#pragma endregion


    //////////////////
    // HDR ���� �ε� //
    //////////////////
#pragma region
    // ��Ÿ ������ ��������
    hr = DirectX::GetMetadataFromHDRFile(texFileName.c_str(), metadata);
    if (SUCCEEDED(hr))
    {
        // HDR ���� �ε�
        hr = DirectX::LoadFromHDRFile(texFileName.c_str(), &metadata, *m_tex);
        if (SUCCEEDED(hr))
        {
            // ���̴� ���ҽ� �信 �ڿ� �Ҵ�
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
    // �ؽ��� std::map�� ���ϴ� �ؽ��İ� �̹� �ε�Ǽ� �����ϴ� ���, filename �� ��ġ�ϴ� �� ã�� texture �� ����
    auto iter = m_map.find(loadFileName);
    if (iter != m_map.end())
    {
        return iter->second.get();
    }

    // �ؽ��� std::map �� ���ϴ� �ؽ��İ� ���� ���, �ؽ��� �ε� �� std::map �� (filename, texture) �� ���� �� �ؽ��� ����
    std::shared_ptr<MyTexture> pTex = std::make_shared<MyTexture>();
    if (pTex->Load(m_pd3dDevice, m_pd3dContext, loadFileName))
    {
        m_map.emplace(loadFileName, pTex);
        return pTex.get();  // .get(): shared_ptr ���, ������ ���ҽ��� �ּҸ� ������ �� �̰� �����! ����Ʈ �����Ϳ��� . �� -> �� �۵�����
    }

    return nullptr;
}

bool MyTextureMgr::Release()
{
    // c# �� foreach �� ����� ���
    for (auto iter : m_map)
    {
        // ���� ���� ���� ���� �������� MyTexture �� ������
        iter.second->Release();
    }
    // ���� ��� ���� ����
    m_map.clear();

    return true;
}

MyTextureMgr::~MyTextureMgr()
{
    Release();
}
