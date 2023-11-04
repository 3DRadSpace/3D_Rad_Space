#include "AutoupdaterState.hpp"
#pragma comment(lib,"Urlmon.lib")

AutoupdaterState::AutoupdaterState():
	_refCount(1),
	_currentProgress(0),
	_totalProgress(0),
	_isFinished(false),
	_aborted(false),
	_isInitialized(false)
{
}

HRESULT AutoupdaterState::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;

	*ppvObject = nullptr;

	if(riid == IID_IUnknown || riid == IID_IBindStatusCallback)
	{
		*ppvObject = this;
		this->AddRef();
		return NOERROR;
	}
	return E_NOINTERFACE;
}

ULONG AutoupdaterState::AddRef()
{
	InterlockedIncrement(&_refCount);
	return _refCount;
}

ULONG AutoupdaterState::Release()
{
	ULONG refCount = InterlockedDecrement(&_refCount);
	if (refCount == 0)
		delete this;
	return refCount;
}

HRESULT AutoupdaterState::OnStartBinding(DWORD dwReserved, IBinding* pib)
{
	_isInitialized = true;
	return NOERROR;
}

HRESULT AutoupdaterState::GetPriority(LONG* pnPriority)
{
	*pnPriority = 1;
	return NOERROR;
}

HRESULT AutoupdaterState::OnLowResource(DWORD reserved)
{
	return NOERROR; //MSDN says this is not implemented, therefore we return HRESULT(0)
}

HRESULT AutoupdaterState::OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
{
	_currentProgress = ulProgress;
	_totalProgress = ulProgressMax;
	return _aborted ? E_ABORT : NOERROR;
}

HRESULT AutoupdaterState::OnStopBinding(HRESULT hresult, LPCWSTR szError)
{
	_isFinished = true;
	return hresult;
}

HRESULT AutoupdaterState::GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo)
{
	return NOERROR;
}

HRESULT AutoupdaterState::OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed)
{
	return _aborted ? E_ABORT : NOERROR;
}

HRESULT AutoupdaterState::OnObjectAvailable(const IID& riid, IUnknown* punk)
{
	punk->AddRef();
	return NOERROR;
}

void AutoupdaterState::Create(_Outptr_ AutoupdaterState** autoUpdater)
{
	if (autoUpdater == nullptr) return;
	*autoUpdater = new AutoupdaterState();
}

float AutoupdaterState::GetCurrentProgress() const
{
	return static_cast<float>(_currentProgress) / static_cast<float>(_totalProgress);
}

void AutoupdaterState::Abort()
{
	_aborted = true;
}

bool AutoupdaterState::Finished() const
{
	return _isFinished;
}

bool AutoupdaterState::Initialized() const
{
	return _isInitialized;
}
