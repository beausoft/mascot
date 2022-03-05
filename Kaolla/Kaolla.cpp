#include "../Mascot/Widget.h"
#include "resource.h"

/*
#define ALLOC_UNIT 100
HRGN CreateRgnFromBitmap(HINSTANCE hInstance, UINT uIDBitmap, COLORREF crTransparent) {
    HDC memDC = CreateCompatibleDC(NULL);
    HBITMAP hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(uIDBitmap));
    BITMAP bm = { 0 };
    GetObject(hBitmap, sizeof(bm), &bm);

    BITMAPINFOHEADER bmih = { sizeof(BITMAPINFOHEADER), bm.bmWidth, bm.bmHeight, 1, 32, BI_RGB, 0, 0, 0, 0, 0 };

    VOID* pBits;
    HBITMAP hDIB = ::CreateDIBSection(memDC, (BITMAPINFO*)&bmih, DIB_RGB_COLORS, &pBits, NULL, 0);
    HBITMAP holdBmp = (HBITMAP)::SelectObject(memDC, hDIB);

    HDC dc = CreateCompatibleDC(memDC);

    // Get how many bytes per row (rounded up to 32 bits)
    BITMAP dib = { 0 };
    ::GetObject(hDIB, sizeof(BITMAP), &dib);
    while (dib.bmWidthBytes % 4)
    {
        dib.bmWidthBytes++;
    }

    // Copy the bitmap into the memory DC
    HBITMAP holdBmp2 = (HBITMAP)::SelectObject(dc, hBitmap);
    BitBlt(memDC, 0, 0, bm.bmWidth, bm.bmHeight, dc, 0, 0, SRCCOPY);

    // alloc some memory using the ALLOC_UNIT
    DWORD maxRect = ALLOC_UNIT;
    HANDLE hData = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRect));

    // fill in the fields, just follow the rules
    RGNDATA* pRgnData = (RGNDATA*)::GlobalLock(hData);
    pRgnData->rdh.dwSize = sizeof(RGNDATAHEADER);
    pRgnData->rdh.iType = RDH_RECTANGLES; // RDH_RECTANGLES eqs 1
    pRgnData->rdh.nCount = pRgnData->rdh.nRgnSize = 0;
    ::SetRect(&pRgnData->rdh.rcBound, 0, 0, MAXLONG, MAXLONG);

    // Get the R,G,B value of the transparent color
    BYTE r0 = GetRValue(crTransparent);
    BYTE g0 = GetGValue(crTransparent);
    BYTE b0 = GetBValue(crTransparent);

    // scan each bitmap row from bottom to top
    BYTE* pRow = (BYTE*)dib.bmBits + (dib.bmHeight - 1) * dib.bmWidthBytes;
    for (int y = 0; y x0)
    {
        // Add the rectangle of (x0, y)-(x, y+1)
        if (pRgnData->rdh.nCount >= maxRect) // if need more rectangles
        {
            // reallocate memory
            ::GlobalUnlock(hData);
            maxRect += ALLOC_UNIT;
            hData = ::GlobalReAlloc(hData, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRect), GMEM_MOVEABLE);
            pRgnData = (RGNDATA*)::GlobalLock(hData);
        }
        RECT* lpRect = (RECT*)&pRgnData->Buffer;
        ::SetRect(&lpRect[pRgnData->rdh.nCount], x0, y, x, y + 1);
        pRgnData->rdh.nCount++;
    }
} // for x
pRow -= dib.bmWidthBytes; // go one row upper
} // for y


// Create a region consisted of the rectangles
HRGN hRgn = ::ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRect), pRgnData);
::GlobalFree((HGLOBAL)pRgnData);

// do some cleaning up work
::SelectObject(dc.m_hDC, holdBmp2);
::DeleteObject(::SelectObject(memDC.m_hDC, holdBmp));
dc.DeleteDC();
memDC.DeleteDC();
bitmap.DeleteObject();
return hRgn;

    
    return NULL;
}
*/

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    Widget widget(hInstance, L"Kaolla", 30, 30, 64, 96);
    widget.SetShapeFromBitmap(IDB_USUAL);
    widget.Show();



    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
