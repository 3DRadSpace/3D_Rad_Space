#include "UpdateDownloadManager.hpp"

HRESULT __stdcall UpdateDownloadManager::OnStartBinding(DWORD dwReserved, __RPC__in_opt IBinding* pib)
{
    return NOERROR; //E_NOTIMPL default code
}

HRESULT __stdcall UpdateDownloadManager::GetPriority(__RPC__out LONG* pnPriority)
{
    *pnPriority = 1;
    return NOERROR;
}

HRESULT __stdcall UpdateDownloadManager::OnLowResource(DWORD reserved)
{
    return NOERROR;
}

HRESULT __stdcall UpdateDownloadManager::OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, __RPC__in_opt LPCWSTR szStatusText)
{
    if (_abort) return E_ABORT;

    _progress = ulProgress;
    _progressMax = ulProgressMax;
    _statusCode = ulStatusCode;
    return NO_ERROR;
}

HRESULT __stdcall UpdateDownloadManager::OnStopBinding(HRESULT hresult, __RPC__in_opt LPCWSTR szError)
{
    _finished = true;
    return NOERROR;
}

HRESULT __stdcall UpdateDownloadManager::GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo)
{
    return NOERROR;
}

HRESULT __stdcall UpdateDownloadManager::OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed)
{
    return NOERROR;
}

HRESULT __stdcall UpdateDownloadManager::OnObjectAvailable(__RPC__in REFIID riid, __RPC__in_opt IUnknown* punk)
{
    return NOERROR;
}

HRESULT __stdcall UpdateDownloadManager::QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
{
    if (ppvObject == nullptr) return E_INVALIDARG;
    *ppvObject = nullptr;

    if (riid == IID_IUnknown)
    {
        *ppvObject = (LPVOID)this;
        AddRef();
        return NOERROR;
    }

    return E_NOINTERFACE;
}

ULONG __stdcall UpdateDownloadManager::AddRef()
{
    _counter += 1;
    return _counter;
}

ULONG __stdcall UpdateDownloadManager::Release()
{
    int c = _counter;
    _counter -= 1;
    if (_counter == 0) delete this;
    return c;
}

unsigned long UpdateDownloadManager::GetProgress()
{
    return _progress;
}

unsigned long UpdateDownloadManager::GetProgressMax()
{
    return _progressMax;
}

unsigned long UpdateDownloadManager::GetStatusCode()
{
    return _statusCode;
}

bool UpdateDownloadManager::GetFinishedState()
{
    return _finished;
}

void UpdateDownloadManager::Abort()
{
    _abort = true;
}

UpdateDownloadManager::~UpdateDownloadManager()
{
    if (DestructorNotFunc != nullptr)
        DestructorNotFunc(this->_progress,this->_statusCode);
}
