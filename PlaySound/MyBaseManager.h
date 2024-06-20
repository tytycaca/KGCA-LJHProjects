#pragma once
#include "MyStd.h"
#include <tchar.h>

class MyResource
{
public:
	std::wstring m_csName = L"none";
public:
	virtual void Set(ID3D11Device* pDevice) {};
	virtual void Release() = 0;
	virtual bool Load(std::wstring filename) = 0;
};

template<class T>
class MySingleton
{
public:
	static T& Get()
	{
		static T mgr;
		return mgr;
	}
};

template <class T, class S>
class MyBaseManager : public MySingleton<S>
{
public:
	std::wstring m_csName = L"None";
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
	std::map<std::wstring, std::shared_ptr<T>> m_list;

public:
	void Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
	{
		m_pd3dDevice = pd3dDevice;
		m_pContext = pContext;
	}
	virtual std::shared_ptr<T> Load(std::wstring filename);
	std::shared_ptr<T> GetPtr(std::wstring key);
	void Release();
	virtual std::shared_ptr<T> CreateObject(std::wstring path, std::wstring name);
	std::wstring SplitPath(std::wstring path, std::wstring entry);

public:
	MyBaseManager() {}
	virtual ~MyBaseManager()
	{
	}
};

template <class T, class S>
std::shared_ptr<T> MyBaseManager<T, S>::Load(std::wstring fullpath)
{
	// 파일명 + 확장자 검출
	std::wstring name = SplitPath(fullpath, L"");
	// 중복 검증
	std::shared_ptr<T> pFindData = GetPtr(name);
	if (pFindData != nullptr)
	{
		return pFindData;
	}

	return CreateObject(fullpath, name);
}

template <class T, class S>
std::shared_ptr<T>  MyBaseManager<T, S>::CreateObject(
	std::wstring path, std::wstring name)
{
	std::shared_ptr<T>  pData = std::make_shared<T>();
	pData->Set(m_pd3dDevice);
	pData->m_csName = name;
	if (pData->Load(path) == false)
	{
		//delete pData;
		return nullptr;
	}
	m_list.insert(std::make_pair(pData->m_csName, pData));
	return pData;
}

template <class T, class S>
std::shared_ptr<T> MyBaseManager<T, S>::GetPtr(std:: wstring key)
{
	auto iter = m_list.find(key);
	if (iter != m_list.end())
	{
		return (*iter).second;
	}

	return nullptr;
}

template<class T, class S>
void MyBaseManager<T, S>::Release()
{
	for (auto pData : m_list)
	{
		std::shared_ptr<T>  data = pData.second;
		data->Release();
	}

	m_list.clear();
}

template <class T, class S>
std::wstring MyBaseManager<T, S>::SplitPath(std::wstring path, std::wstring entry)
{
	wchar_t szDrive[MAX_PATH] = { 0, };
	wchar_t szDir[MAX_PATH] = { 0, };
	wchar_t szFileName[MAX_PATH] = { 0, };
	wchar_t szFileExt[MAX_PATH] = { 0, };

	_tsplitpath_s(path.c_str(), szDrive, szDir, szFileName, szFileExt);
	std::wstring name = szFileName;
	name += szFileExt;
	if (entry.empty() == false)
	{
		name += entry;
	}

	return name;
}