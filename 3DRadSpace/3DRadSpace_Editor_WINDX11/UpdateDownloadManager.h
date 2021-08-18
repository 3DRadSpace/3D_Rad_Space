#include <Windows.h>

class UpdateDownloadManager : IBindStatusCallback
{
public:
	HRESULT __stdcall OnStartBinding(DWORD dwReserved, __RPC__in_opt IBinding* pib) override;
    HRESULT __stdcall GetPriority(__RPC__out LONG* pnPriority) override;
    HRESULT __stdcall OnLowResource(DWORD reserved) override;
    HRESULT __stdcall OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, __RPC__in_opt LPCWSTR szStatusText) override;
    HRESULT __stdcall OnStopBinding(HRESULT hresult, __RPC__in_opt LPCWSTR szError) override;
    HRESULT __stdcall GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo) override;
    HRESULT __stdcall OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed) override;
    HRESULT __stdcall OnObjectAvailable(__RPC__in REFIID riid,__RPC__in_opt IUnknown* punk) override;
};
