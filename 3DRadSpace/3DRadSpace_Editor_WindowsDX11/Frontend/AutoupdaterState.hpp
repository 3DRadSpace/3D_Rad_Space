#pragma once
#include <Urlmon.h>

class AutoupdaterState : public IBindStatusCallback
{
	ULONG _refCount;

	ULONG _currentProgress;
	ULONG _totalProgress;

	bool _isFinished;
	bool _aborted;
	bool _isInitialized;


	AutoupdaterState();
public:

	AutoupdaterState(AutoupdaterState&) = delete;
	AutoupdaterState(AutoupdaterState&&) = delete;

	AutoupdaterState& operator=(AutoupdaterState&) = delete;
	AutoupdaterState& operator=(AutoupdaterState&&) = delete;

	//Implements IUnknown

	HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
	ULONG AddRef() override;
	ULONG Release() override;

	//Implementing IBindStatusCallback

	HRESULT OnStartBinding(DWORD dwReserved, IBinding* pib) override;
	HRESULT GetPriority(LONG* pnPriority) override;
	HRESULT OnLowResource(DWORD reserved) override;
	HRESULT OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText) override;
	HRESULT OnStopBinding(HRESULT hresult, LPCWSTR szError) override;
	HRESULT GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo) override;
	HRESULT OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed) override;
	HRESULT OnObjectAvailable(const IID& riid, IUnknown* punk) override;

	//AutoupdaterState
	static void Create(_Outptr_ AutoupdaterState** autoUpdater);

	float GetCurrentProgress() const;
	void Abort();
	bool Finished() const;
	bool Initialized() const;

	virtual ~AutoupdaterState() = default;
};

