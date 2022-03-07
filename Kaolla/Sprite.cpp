#include "Sprite.h"
#include <windowsx.h>
#include "OptionsDlg.h"
#include "resource.h"
#include <cmath>

Sprite::Sprite(HINSTANCE hInstance, LPCWSTR spriteName, INT nWidth, INT nHeight, const OPTIONS* options)
{
    INT x = 0, y = 0;
    if (hInstance == NULL) {
        m_hInstance = GetModuleHandle(NULL);
    }
    else {
        m_hInstance = hInstance;
    }
    static int WndIdx = 0;
    WCHAR szWindowClass[32] = { 0 };
    wsprintf(szWindowClass, L"Mascot-%s-%d", spriteName, WndIdx++);

    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Sprite::WndProc;
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
    CreateWindow(szWindowClass, spriteName, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, x, y, nWidth, nHeight, nullptr, nullptr, m_hInstance, (LPVOID)this);
    // 初始化菜单
    m_popupMenu = LoadMenu(m_hInstance, MAKEINTRESOURCE(IDR_MENUPOPUP));
    // 设置参数
    if (options != NULL) {
        memcpy(&m_options, options, sizeof(OPTIONS));
    }
}

Sprite::~Sprite()
{
    if (m_hWnd != NULL) {
        DestroyWindow(m_hWnd);
    }
}

LRESULT Sprite::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 1. WM_NCCREATE、2. WM_NCCALCSIZE、3. WM_CREATE
    Sprite* pSprite = NULL;
    if (message == WM_CREATE) {
        pSprite = (Sprite*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
        pSprite->m_hWnd = hWnd;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pSprite);
    }
    else {
        pSprite = (Sprite*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }
    if (pSprite != NULL) {
        switch (message)
        {
            HANDLE_MSG(hWnd, WM_CREATE, pSprite->OnCreate);
            HANDLE_MSG(hWnd, WM_CLOSE, pSprite->OnClose);
            HANDLE_MSG(hWnd, WM_DESTROY, pSprite->OnDestroy);
            HANDLE_MSG(hWnd, WM_DISPLAYCHANGE, pSprite->OnDisplayChange);
            HANDLE_MSG(hWnd, WM_NCHITTEST, pSprite->OnNCHitTest);
            HANDLE_MSG(hWnd, WM_PAINT, pSprite->OnPaint);
            HANDLE_MSG(hWnd, WM_ACTIVATE, pSprite->OnActivate);
            HANDLE_MSG(hWnd, WM_TIMER, pSprite->OnTimer);
            HANDLE_MSG(hWnd, WM_RBUTTONUP, pSprite->OnRButtonUp);
            HANDLE_MSG(hWnd, WM_LBUTTONDOWN, pSprite->OnLButtonDown);
            HANDLE_MSG(hWnd, WM_LBUTTONUP, pSprite->OnLButtonUp);
            HANDLE_MSG(hWnd, WM_MOUSEMOVE, pSprite->OnMouseMove);
            HANDLE_MSG(hWnd, WM_COMMAND, pSprite->OnCommand);
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

HWND Sprite::GetHandle()
{
    return m_hWnd;
}

void Sprite::Show()
{
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
    UpdatePosition();
}

void Sprite::Hidden()
{
    ShowWindow(m_hWnd, SW_HIDE);
}

void Sprite::SetFrame(FRAME frame)
{
    m_frame = frame;
    HDC hdc = GetDC(m_hWnd);
    UpdateShape(hdc);
    ReleaseDC(m_hWnd, hdc);
}

int Sprite::EventLoop()
{
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

void Sprite::PlayAnimation(const ACTION* pAction)
{
    if (!m_options.ANIMATION) {
        return;
    }
    StopAnimation();
    if (pAction->sound != NULL && m_options.SOUND) {
        PlaySound(MAKEINTRESOURCE(pAction->sound), m_hInstance, SND_ASYNC | SND_RESOURCE | SND_NODEFAULT | SND_NOWAIT);
    }
    m_AnimationStatus.running = TRUE;
    m_AnimationStatus.action = pAction;
    m_AnimationStatus.frameIndex = 0;
    SetTimer(m_hWnd, IDT_ANIMATION, pAction->interval, NULL);
}

void Sprite::StopAnimation()
{
    if (m_AnimationStatus.running) {
        KillTimer(m_hWnd, IDT_ANIMATION);
        SetFrame(m_AnimationStatus.action->frames[m_AnimationStatus.action->length - 1]);  // 停止动画时，将直接展示最后一帧
        /*清理动画状态*/
        m_AnimationStatus.running = FALSE;
        m_AnimationStatus.action = NULL;
        m_AnimationStatus.frameIndex = 0;
    }
}

void Sprite::UpdateShape(HDC hdc)
{
    if (!m_frame.idBitmap) return;
    HBITMAP hBitmap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(m_frame.idBitmap));
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

void Sprite::UpdatePosition()
{
    if (m_options.selection == SELECTION::StartMenu) {
        RECT wndRect;
        GetWindowRect(m_hWnd, &wndRect);
        int screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
        int wndWidth = wndRect.right - wndRect.left;
        int wndHeight = wndRect.bottom - wndRect.top;

        int x = int((screenWidth - wndWidth) * (m_options.WINPOS / 100.f)) + m_frame.offsetX;
        int y = screenHeight - wndHeight + m_frame.offsetY;
        MoveWindow(m_hWnd, x, y, wndWidth, wndHeight, TRUE);
    }
}

BOOL Sprite::OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
    SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
    SetLayeredWindowAttributes(hWnd, RGB(0, 250, 250), 255, LWA_COLORKEY);   // LWA_ALPHA | LWA_COLORKEY
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    return TRUE;
}

void Sprite::OnClose(HWND hwnd)
{
    DestroyWindow(hwnd);
}

void Sprite::OnDestroy(HWND hWnd)
{
    m_hWnd = NULL;   // 窗口被销毁，清除句柄引用
    PostQuitMessage(0);    // 发送结束程序消息
}

void Sprite::OnDisplayChange(HWND hwnd, UINT bitsPerPixel, UINT cxScreen, UINT cyScreen)
{
    // 监听分辨率改变事件
    UpdatePosition();
}

UINT Sprite::OnNCHitTest(HWND hwnd, int x, int y)
{
    return HTCLIENT;
}

void Sprite::OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    UpdateShape(hdc);
    EndPaint(hWnd, &ps);
}

void Sprite::OnActivate(HWND hWnd, UINT state, HWND hwndActDeact, BOOL fMinimized)
{
    if ((state == WA_ACTIVE || state == WA_CLICKACTIVE) && !fMinimized) {
        // 窗口激活时进行置前操作
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
}

void Sprite::OnTimer(HWND hWnd, UINT id)
{
    if (id == IDT_ANIMATION) {
        if (m_AnimationStatus.running) {
            const ACTION *pAction = m_AnimationStatus.action;
            if (pAction->length > 0) {
                SetFrame(pAction->frames[m_AnimationStatus.frameIndex]);
                if (m_AnimationStatus.frameIndex + 1 < pAction->length - 1) {
                    m_AnimationStatus.frameIndex = m_AnimationStatus.frameIndex + 1;
                }
                else {
                    if (pAction->loop) {
                        m_AnimationStatus.frameIndex = 0;
                    }
                    else {
                        StopAnimation();
                    }
                }
            }
        }
    }
}

void Sprite::OnRButtonUp(HWND hWnd, int x, int y, UINT flags)
{
    POINT pt = { 0 };
    GetCursorPos(&pt);
    SetForegroundWindow(hWnd);

    HMENU hMenu = GetSubMenu(m_popupMenu, 0);
    TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, NULL, hWnd, NULL);
}

void Sprite::OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    if (!fDoubleClick) {
        SetCapture(hwnd);	//独占鼠标消息
        m_isMousePrees = TRUE;
        m_mouseXY.x = x;
        m_mouseXY.y = y;
    }
}

void Sprite::OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    if (m_isMousePrees) {
        m_isMousePrees = FALSE;
        m_mouseXY.x = 0;
        m_mouseXY.y = 0;
        ReleaseCapture();  //释放独占鼠标消息

        // 更新位置
        RECT wndRect;
        GetWindowRect(hwnd, &wndRect);
        int pos = int(wndRect.left / float(GetSystemMetrics(SM_CXFULLSCREEN) - (wndRect.right - wndRect.left)) * 100);
        if (std::abs(pos - int(m_options.WINPOS)) > 2) {
            m_options.WINPOS = int(wndRect.left / float(GetSystemMetrics(SM_CXFULLSCREEN) - (wndRect.right - wndRect.left)) * 100);
        }
        UpdatePosition();
    }
}

void Sprite::OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
    if (m_isMousePrees) {
        RECT winRect = { 0 };
        GetWindowRect(hwnd, &winRect);	//获取窗口大小
        int cx = winRect.left + (x - m_mouseXY.x);
        int cy = winRect.top + (y - m_mouseXY.y);
        MoveWindow(hwnd, cx, cy, winRect.right - winRect.left, winRect.bottom - winRect.top, TRUE);	//移动窗口
    }
}

INT_PTR CALLBACK AboutDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void Sprite::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id) {
    case ID_POPUP_SETTINGS:
        Hidden();
        OptionsDlg::ShowDialog(m_hInstance, hwnd, &m_options);
        Show();
        break;
    case ID_POPUP_ABOUT:
        DialogBox(m_hInstance, MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDialogProc);
        break;
    case ID_POPUP_QUIT:
        break;
    case ID_POPUP_EXIT:
        DestroyWindow(hwnd);
        break;
    }
}
