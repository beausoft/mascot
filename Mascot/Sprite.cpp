#include "Sprite.h"

Sprite::Sprite(HINSTANCE hInstance, LPCWSTR spriteName, INT x, INT y, INT nWidth, INT nHeight)
{
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
}

Sprite::~Sprite()
{
    if (m_hWnd != NULL) {
        DestroyWindow(m_hWnd);
    }
    while (!m_Actions.empty()) {
        LPACTION pAction = m_Actions.back();
        m_Actions.pop_back();
        free(pAction);
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
            HANDLE_MSG(hWnd, WM_DESTROY, pSprite->OnDestroy);
            HANDLE_MSG(hWnd, WM_DISPLAYCHANGE, pSprite->OnDisplayChange);
            HANDLE_MSG(hWnd, WM_NCHITTEST, pSprite->OnNCHitTest);
            HANDLE_MSG(hWnd, WM_PAINT, pSprite->OnPaint);
            HANDLE_MSG(hWnd, WM_ACTIVATE, pSprite->OnActivate);
            HANDLE_MSG(hWnd, WM_TIMER, pSprite->OnTimer);
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
}

void Sprite::Hidden()
{
    ShowWindow(m_hWnd, SW_HIDE);
}

void Sprite::SetShapeFromBitmap(UINT uIDBitmap)
{
    m_uIDBitmap = uIDBitmap;
    HDC hdc = GetDC(m_hWnd);
    UpdateShape(hdc);
    ReleaseDC(m_hWnd, hdc);
}

const int Sprite::CreateAction(const UINT* frames, int framesLength, int interval, UINT sound)
{
    LPACTION action = (LPACTION)malloc(sizeof(ACTION) + framesLength * sizeof(UINT));
    if (action == NULL) {
        // 判断内存是否申请成功
        return -1;
    }
    action->sound = sound;
    action->interval = interval;
    action->length = framesLength;
    memcpy(action->frames, frames, framesLength * sizeof(UINT));
    m_Actions.push_back(action);
    return m_Actions.size() - 1;
}

void Sprite::PerformAnimation(UINT actionIndex)
{
    if (actionIndex >= 0 && actionIndex < m_Actions.size()) {
        if (m_AnimationStatus.running == FALSE) {
            LPACTION action = m_Actions.at(actionIndex);
            m_AnimationStatus.running = TRUE;
            m_AnimationStatus.actionIndex = actionIndex;
            m_AnimationStatus.frameIndex = 0;
            SetTimer(GetHandle(), IDT_ANIMATION, action->interval, NULL);
        }
    }
    
}

void Sprite::UpdateShape(HDC hdc)
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

BOOL Sprite::OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
    SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
    SetLayeredWindowAttributes(hWnd, RGB(0, 250, 250), 255, LWA_COLORKEY);   // LWA_ALPHA | LWA_COLORKEY
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    return TRUE;
}

void Sprite::OnDestroy(HWND hWnd)
{
    m_hWnd = NULL;   // 窗口被销毁，清除句柄引用
    PostQuitMessage(0);    // 发送结束程序消息
}

void Sprite::OnDisplayChange(HWND hwnd, UINT bitsPerPixel, UINT cxScreen, UINT cyScreen)
{
    // TODO 监听分辨率改变事件
}

UINT Sprite::OnNCHitTest(HWND hwnd, int x, int y)
{
    return HTCAPTION;  // https://blog.csdn.net/jiangqin115/article/details/45057417
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
            LPACTION pAction = m_Actions.at(m_AnimationStatus.actionIndex);
            SetShapeFromBitmap(pAction->frames[m_AnimationStatus.frameIndex]);
            if (m_AnimationStatus.frameIndex + 1 < pAction->length) {
                m_AnimationStatus.frameIndex = m_AnimationStatus.frameIndex + 1;
            }
            else {
                KillTimer(hWnd, IDT_ANIMATION);
                m_AnimationStatus.actionIndex = 0;
                m_AnimationStatus.frameIndex = 0;
                m_AnimationStatus.running = FALSE;
            }
        }
    }
}
