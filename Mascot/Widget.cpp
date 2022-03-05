#include "Widget.h"

Widget::Widget(HINSTANCE hInst, LPCWSTR name, INT x, INT y, INT nWidth, INT nHeight)
{
	if (hInst == NULL) {
		hInst = GetModuleHandle(NULL);
	}
    m_hInstance = hInst;
	static int WndIdx = 0;
	WCHAR szWindowClass[32] = { 0 };
    wsprintf(szWindowClass, L"MascotWidget-%s-%d", name, WndIdx++);

    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Widget::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = NULL;

    if (!RegisterClassEx(&wcex)) {
        return;
    }
    CreateWindow(szWindowClass, name, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, x, y, nWidth, nHeight, nullptr, nullptr, m_hInstance, (LPVOID)this);
}

Widget::~Widget()
{
    if (this->m_hWnd != NULL) {
        DestroyWindow(this->m_hWnd);
    }
}

LRESULT Widget::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 1. WM_NCCREATE、2. WM_NCCALCSIZE、3. WM_CREATE
    Widget* pWidget = NULL;
    if (message == WM_CREATE) {
        pWidget = (Widget*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
        pWidget->m_hWnd = hWnd;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWidget);
    }
    else {
        pWidget = (Widget*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }
    if (pWidget != NULL) {
        switch (message)
        {
            HANDLE_MSG(hWnd, WM_CREATE, pWidget->OnCreate);
            HANDLE_MSG(hWnd, WM_DESTROY, pWidget->OnDestroy);
            HANDLE_MSG(hWnd, WM_DISPLAYCHANGE, pWidget->OnDisplayChange);
            HANDLE_MSG(hWnd, WM_NCHITTEST, pWidget->OnNCHitTest);
            HANDLE_MSG(hWnd, WM_PAINT, pWidget->OnPaint);
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

HWND Widget::GetHandle()
{
    return m_hWnd;
}

void Widget::Show()
{
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
}

void Widget::Hide()
{
    ShowWindow(m_hWnd, SW_HIDE);
}

void Widget::SetShapeFromBitmap(UINT uIDBitmap)
{
    m_uIDBitmap = uIDBitmap;
    HDC hdc = GetDC(m_hWnd);
    UpdateShape(hdc);
    ReleaseDC(m_hWnd, hdc);
}

void Widget::UpdateShape(HDC hdc)
{
    if (!m_uIDBitmap) return;
    HBITMAP hBitmap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(m_uIDBitmap));
    BITMAP bm = { 0 };
    GetObject(hBitmap, sizeof(bm), &bm);
    //BITMAPINFOHEADER bmih = { sizeof(BITMAPINFOHEADER), bm.bmWidth, bm.bmHeight, 1, 32, BI_RGB, 0, 0, 0, 0, 0 };

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hBitmapOld = (HBITMAP)SelectObject(memDC, hBitmap);
    BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, hBitmapOld);

    DeleteDC(memDC);
    DeleteObject(hBitmap);
}

BOOL Widget::OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
    SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
    SetLayeredWindowAttributes(hWnd, RGB(0, 250, 250), 255, LWA_COLORKEY);   // LWA_ALPHA | LWA_COLORKEY
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    return TRUE;
}

void Widget::OnDestroy(HWND hWnd)
{
    this->m_hWnd = NULL;   // 窗口被销毁，清除句柄引用
    PostQuitMessage(0);    // 发送结束程序消息
}

void Widget::OnDisplayChange(HWND hwnd, UINT bitsPerPixel, UINT cxScreen, UINT cyScreen)
{
    // TODO 监听分辨率改变事件
}

UINT Widget::OnNCHitTest(HWND hwnd, int x, int y)
{
    return HTCAPTION;  // https://blog.csdn.net/jiangqin115/article/details/45057417
}

void Widget::OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    UpdateShape(hdc);
    EndPaint(hWnd, &ps);
}
