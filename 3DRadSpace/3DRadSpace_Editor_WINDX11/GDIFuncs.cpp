#include "GDIFuncs.hpp"

Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;

void InitializeGDI()
{
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
}

HBITMAP loadImgResource(wchar_t* pName, wchar_t* pType, HMODULE hInst)
{
    HBITMAP result = nullptr;

    HRSRC hResource = FindResource(hInst, pName, pType);
    if(!hResource)
        return nullptr;

    DWORD imgSize = SizeofResource(hInst, hResource);
    if(!imgSize)
        return nullptr;

    HGLOBAL resource = LoadResource(hInst, hResource);
    if(resource == nullptr)
        return nullptr;
    const void* pResourceData = LockResource(resource);
    if(!pResourceData)
        return nullptr;

    HANDLE m_hBuffer = GlobalAlloc(GMEM_MOVEABLE, imgSize);
    if(m_hBuffer)
    {
        void* pBuffer = GlobalLock(m_hBuffer);
        if(pBuffer)
        {
            CopyMemory(pBuffer, pResourceData, imgSize);
            IStream* pStream = NULL;
            if(CreateStreamOnHGlobal(m_hBuffer, FALSE, &pStream) == S_OK)
            {
                Gdiplus::Bitmap* m_pBitmap = Gdiplus::Bitmap::FromStream(pStream);
                pStream->Release();
                if(m_pBitmap)
                {
                    if(m_pBitmap->GetLastStatus() == Gdiplus::Ok)
                    {
                        m_pBitmap->GetHBITMAP(0, &result);
                        delete m_pBitmap;
                    }
                }
            }
            GlobalUnlock(m_hBuffer);
        }
        GlobalFree(m_hBuffer);
    }
    return result;
}

HBITMAP loadImgResource(WORD resNum, LPWSTR pType)
{
    return loadImgResource(MAKEINTRESOURCE(resNum), pType, GetModuleHandle(0));//hInst);
}

void DeinitializeGDI()
{
   Gdiplus::GdiplusShutdown(gdiplusToken);
}
