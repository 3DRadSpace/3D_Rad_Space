#pragma once
#include "Libs.hpp"

typedef void (*UpdateDownloadManagerDestructorNotifier)(unsigned long& progress, unsigned long& status);

class UpdateDownloadManager : public IBindStatusCallback
{
    int _counter;
    unsigned long _progress;
    unsigned long _progressMax;
    unsigned long _statusCode;
    bool _finished;
    bool _abort;
public:
    UpdateDownloadManager() : _counter(1),_progress(0),_progressMax(1),_statusCode(0),_finished(false),_abort(false), DestructorNotFunc(nullptr){};
	
    UpdateDownloadManagerDestructorNotifier DestructorNotFunc;

    HRESULT __stdcall OnStartBinding(DWORD dwReserved, __RPC__in_opt IBinding* pib) override;
    HRESULT __stdcall GetPriority(__RPC__out LONG* pnPriority) override;
    HRESULT __stdcall OnLowResource(DWORD reserved) override;
    HRESULT __stdcall OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, __RPC__in_opt LPCWSTR szStatusText) override;
    HRESULT __stdcall OnStopBinding(HRESULT hresult, __RPC__in_opt LPCWSTR szError) override;
    HRESULT __stdcall GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo) override;
    HRESULT __stdcall OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed) override;
    HRESULT __stdcall OnObjectAvailable(__RPC__in REFIID riid,__RPC__in_opt IUnknown* punk) override;

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject) override;
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();

    unsigned long GetProgress();
    unsigned long GetProgressMax();
    unsigned long GetStatusCode();
    bool GetFinishedState();
    void Abort();

    ~UpdateDownloadManager();

};
