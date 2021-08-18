
#include "UpdateDownloadManager.h"

HRESULT __stdcall UpdateDownloadManager::OnStartBinding(DWORD dwReserved, IBinding* pib)
{
    return E_NOTIMPL;
}

HRESULT __stdcall UpdateDownloadManager::GetPriority(LONG* pnPriority)
{
    return E_NOTIMPL;
}

HRESULT __stdcall UpdateDownloadManager::OnLowResource(DWORD reserved)
{
    return E_NOTIMPL;
}

HRESULT __stdcall UpdateDownloadManager::OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
{
    return 0;
}

HRESULT __stdcall UpdateDownloadManager::OnStopBinding(HRESULT hresult, LPCWSTR szError)
{
    return E_NOTIMPL;
}

HRESULT __stdcall UpdateDownloadManager::GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo)
{
    return E_NOTIMPL;
}

HRESULT __stdcall UpdateDownloadManager::OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed)
{
    return E_NOTIMPL;
}

HRESULT __stdcall UpdateDownloadManager::OnObjectAvailable(REFIID riid, IUnknown* punk)
{
    return E_NOTIMPL;
}
