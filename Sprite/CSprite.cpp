#include "CSprite.h"
#include <windowsx.h>
#include <cmath>
#include <Psapi.h>
#include <string>
#include <algorithm>
#include "resource.h"
#include "COptionsDlg.h"
#include <vector>
#include <Commctrl.h>

BOOL isExplorer(_In_ HWND hWnd) {
    DWORD dwPid;
    if (GetWindowThreadProcessId(hWnd, &dwPid)) {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwPid);
        if (NULL != hProcess) {
            WCHAR fileFullName[MAX_PATH] = { 0 };
            if (GetProcessImageFileName(hProcess, fileFullName, MAX_PATH)) {
                std::wstring fileFullNameString(fileFullName);
                std::wstring::size_type spInd = fileFullNameString.find_last_of('\\', fileFullNameString.length());
                if (std::wstring::npos != spInd) {
                    std::wstring fileNameString = fileFullNameString.substr(spInd + 1, fileFullNameString.length());
                    std::transform(fileNameString.begin(), fileNameString.end(), fileNameString.begin(), ::tolower);
                    if (fileNameString == L"explorer.exe") {
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}

BOOL isSelf(_In_ HWND hWnd) {
    DWORD dwPid = NULL;
    if (GetWindowThreadProcessId(hWnd, &dwPid)) {
        DWORD dwMyPid = GetCurrentProcessId();
        if (dwPid == dwMyPid) {
            return TRUE;
        }
    }
    WCHAR className[64] = { 0 };
    if (GetClassName(hWnd, className, 64)) {
        std::wstring classNameStr(className);
        if (classNameStr.find(L"BeausoftMascot-") == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
    std::vector<HWND>* list = (std::vector<HWND>*)lParam;
    WCHAR className[64] = { 0 };
    if (GetClassName(hWnd, className, 63)) {
        std::wstring classNameStr(className);
        if (classNameStr.find(L"BeausoftMascot-") == 0) {
            list->push_back(hWnd);
        }
    }
    return TRUE;
}

CSprite::CSprite(HINSTANCE hInstance, LPCWSTR spriteName, INT nWidth, INT nHeight, const OPTIONS* options)
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
    wsprintf(szWindowClass, L"BeausoftMascot-%s-%d", spriteName, WndIdx++);

    WNDCLASSEXW wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = CSprite::WndProc;
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
    // ��ʼ���˵�
    extern HINSTANCE g_hInst;
    m_popupMenu = GetSubMenu(LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_MENUPOPUP)), 0);
    // ���ò���
    if (options != NULL) {
        memcpy(&m_options, options, sizeof(OPTIONS));
    }
}

CSprite::~CSprite()
{
    if (m_hWnd != NULL) {
        DestroyWindow(m_hWnd);
    }
}

LRESULT CSprite::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 1. WM_NCCREATE��2. WM_NCCALCSIZE��3. WM_CREATE
    CSprite* pSprite = NULL;
    if (message == WM_CREATE) {
        pSprite = (CSprite*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
        pSprite->m_hWnd = hWnd;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pSprite);
    }
    else {
        pSprite = (CSprite*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
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
            HANDLE_MSG(hWnd, WM_INITMENUPOPUP, pSprite->OnInitMenuPopup);
        case WM_UNINITMENUPOPUP:
            pSprite->OnUnInitMenuPopup(hWnd, (HMENU)wParam);
            return 0L;
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

HWND CSprite::GetHandle()
{
    return m_hWnd;
}

void CSprite::Show()
{
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
    UpdatePosition();
}

void CSprite::Hidden()
{
    ShowWindow(m_hWnd, SW_HIDE);
}

void CSprite::SetFrame(FRAME frame)
{
    bool updatePos = m_frame.offsetX != frame.offsetX || m_frame.offsetY != frame.offsetY;
    m_frame = frame;
    HDC hdc = GetDC(m_hWnd);
    UpdateShape(hdc);
    ReleaseDC(m_hWnd, hdc);
    if (updatePos) {
        UpdatePosition();
    }
}

int CSprite::EventLoop()
{
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

void CSprite::PlayAnimation(const ACTION* pAction)
{
    StopAnimation();
    if (pAction->sound != NULL && m_options.SOUND) {
        PlaySound(MAKEINTRESOURCE(pAction->sound), m_hInstance, SND_ASYNC | SND_RESOURCE | SND_NODEFAULT | SND_NOWAIT);
    }
    if (!m_options.ANIMATION) {
        return;
    }
    m_AnimationStatus.running = TRUE;
    m_AnimationStatus.action = pAction;
    m_AnimationStatus.frameIndex = 0;
    // ��ʼ�Ͳ���
    if (pAction->length > 0) {
        SetFrame(pAction->frames[m_AnimationStatus.frameIndex]);
        m_AnimationStatus.frameIndex = m_AnimationStatus.frameIndex + 1;
    }
    SetTimer(m_hWnd, IDT_ANIMATION, pAction->interval, NULL);
}

void CSprite::StopAnimation()
{
    if (m_AnimationStatus.running) {
        KillTimer(m_hWnd, IDT_ANIMATION);
        SetFrame(m_AnimationStatus.action->frames[m_AnimationStatus.action->length - 1]);  // ֹͣ����ʱ����ֱ��չʾ���һ֡
        /*������״̬*/
        m_AnimationStatus.running = FALSE;
        m_AnimationStatus.action = NULL;
        m_AnimationStatus.frameIndex = 0;
    }
}

void CSprite::UpdateShape(HDC hdc)
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

void CSprite::UpdatePosition()
{
    RECT wndRect;
    GetWindowRect(m_hWnd, &wndRect);
    int wndWidth = wndRect.right - wndRect.left;
    int wndHeight = wndRect.bottom - wndRect.top;

    RECT targetWndRect = m_ForegroundWndRect;
    if (m_options.selection == SELECTION::StartMenu || (m_options.selection == SELECTION::Either && (m_hWndForeground == NULL || targetWndRect.top - wndHeight < 0))) {
        int screenX = GetSystemMetrics(SM_CXSCREEN);
        int screenY = GetSystemMetrics(SM_CYSCREEN);
        RECT rt;
        SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);
        // ����������߶ȵ�����Ļ�߶�˵��û�������������������ڲ���
        if (rt.bottom != screenY && rt.left == 0 && rt.top == 0) {
            targetWndRect.top = rt.bottom;
            targetWndRect.left = 0;
            targetWndRect.right = GetSystemMetrics(SM_CXSCREEN);
            targetWndRect.bottom = GetSystemMetrics(SM_CYSCREEN);
        }
    }
    else if (m_options.selection == SELECTION::ActiveWindow && (targetWndRect.top - wndHeight < 0 || m_hWndForeground == NULL)) {
        targetWndRect = { 0 };
    }

    if (targetWndRect.top <= 0) {
        // �Ƴ���Ļ��
        MoveWindow(m_hWnd, -wndWidth, -wndHeight, wndWidth, wndHeight, TRUE);
    }
    else {
        int targetWndWidth = targetWndRect.right - targetWndRect.left;
        int targetWndHeight = targetWndRect.bottom - targetWndRect.top;
        int x = int((targetWndWidth - (wndRect.right - wndRect.left)) * (m_options.WINPOS / 100.f) + targetWndRect.left + m_frame.offsetX);
        int y = targetWndRect.top - wndHeight + m_frame.offsetY;
        MoveWindow(m_hWnd, x, y, wndWidth, wndHeight, TRUE);
    }
}

void CSprite::Set_hWndForeground(HWND hWndForeground)
{
    bool change = false;
    if (m_hWndForeground != hWndForeground) {
        change = true;
        m_hWndForeground = hWndForeground;
    }
    if (m_hWndForeground != NULL) {
        RECT foregroundWndRect = { 0 };
        GetWindowRect(m_hWndForeground, &foregroundWndRect);
        if (foregroundWndRect.top != m_ForegroundWndRect.top
            || foregroundWndRect.left != m_ForegroundWndRect.left
            || foregroundWndRect.right != m_ForegroundWndRect.right
            || foregroundWndRect.bottom != m_ForegroundWndRect.bottom) {
            // ֻ�е�ǰ̨����λ�øı�ʱ�Ž���λ�ø���
            m_ForegroundWndRect = foregroundWndRect;
            change = true;
        }
    }
    else {
        m_ForegroundWndRect = { 0 };
    }
    if (change) {
        UpdatePosition();
    }
}

BOOL CSprite::OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
    SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
    SetLayeredWindowAttributes(hWnd, RGB(0, 250, 250), 255, LWA_COLORKEY);   // LWA_ALPHA | LWA_COLORKEY
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    SetTimer(hWnd, IDT_WINDOW_DETECTION, 35, NULL);
    SetTimer(hWnd, IDT_KEEP_TOP, 1000, NULL);
    return TRUE;
}

void CSprite::OnClose(HWND hwnd)
{
    DestroyWindow(hwnd);
}

void CSprite::OnDestroy(HWND hWnd)
{
    KillTimer(hWnd, IDT_ANIMATION);
    KillTimer(hWnd, IDT_WINDOW_DETECTION);
    KillTimer(hWnd, IDT_KEEP_TOP);
    m_hWnd = NULL;   // ���ڱ����٣�����������
    PostQuitMessage(0);    // ���ͽ���������Ϣ
}

void CSprite::OnDisplayChange(HWND hwnd, UINT bitsPerPixel, UINT cxScreen, UINT cyScreen)
{
    // �����ֱ��ʸı��¼�
    UpdatePosition();
}

UINT CSprite::OnNCHitTest(HWND hwnd, int x, int y)
{
    return HTCLIENT;
}

void CSprite::OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    UpdateShape(hdc);
    EndPaint(hWnd, &ps);
}

void CSprite::OnActivate(HWND hWnd, UINT state, HWND hwndActDeact, BOOL fMinimized)
{
    if ((state == WA_ACTIVE || state == WA_CLICKACTIVE) && !fMinimized) {
        // ���ڼ���ʱ������ǰ����
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

void CSprite::OnTimer(HWND hWnd, UINT id)
{
    switch (id) {
    case IDT_ANIMATION:
        if (m_AnimationStatus.running) {
            const ACTION* pAction = m_AnimationStatus.action;
            if (pAction->length > 0) {
                if (m_AnimationStatus.frameIndex + 1 < pAction->length) {
                    SetFrame(pAction->frames[m_AnimationStatus.frameIndex]);
                    m_AnimationStatus.frameIndex = m_AnimationStatus.frameIndex + 1;
                }
                else {
                    if (pAction->loop) {
                        m_AnimationStatus.frameIndex = 0;
                        SetFrame(pAction->frames[m_AnimationStatus.frameIndex]);
                    }
                    else {
                        StopAnimation();
                    }
                }
            }
        }
        break;
    case IDT_WINDOW_DETECTION:
    {
        if (m_options.selection == SELECTION::ActiveWindow || m_options.selection == SELECTION::Either) {
            HWND hWndForeground = GetForegroundWindow();
            if (hWndForeground == NULL) {
                Set_hWndForeground(NULL);
                return;
            }
            if (hWndForeground == m_hWnd || isSelf(hWndForeground)) {
                if (m_hWndForeground != NULL && (!IsWindow(m_hWndForeground) || IsIconic(m_hWndForeground))) {
                    // �����鸽���ڴ�����ʱ�������ڱ��رգ�Ȼ���Լ��л�������Ĵ����ϣ����¾���λ�ò����µ�bug
                    Set_hWndForeground(NULL);   // ������ھ����Ч��˵��������ڱ����٣������ǰ�ô����ÿա�
                }
                return;   // ������Լ��ľ�����򲻽����κβ���
            }
            if (isExplorer(hWndForeground)) {
                Set_hWndForeground(NULL);
            }
            else {
                Set_hWndForeground(hWndForeground);
            }
        }
        else {
            Set_hWndForeground(NULL);
        }
    }
    break;
    case IDT_KEEP_TOP:
        // ��ʱ����ͣ��ˢ���ö�������
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        break;
    }
}

void CSprite::OnRButtonUp(HWND hWnd, int x, int y, UINT flags)
{
    POINT pt = { 0 };
    GetCursorPos(&pt);
    TrackPopupMenu(m_popupMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
}

void CSprite::OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    if (!fDoubleClick) {
        SetCapture(hwnd);	//��ռ�����Ϣ
        m_isMousePrees = TRUE;
        m_mouseXY.x = x;
        m_mouseXY.y = y;

        if (m_ClickHook != nullptr) {
            m_ClickHook();
        }
    }
}

void CSprite::OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    if (m_isMousePrees) {
        m_isMousePrees = FALSE;
        m_mouseXY.x = 0;
        m_mouseXY.y = 0;
        ReleaseCapture();  //�ͷŶ�ռ�����Ϣ

        // ����λ��
        RECT wndRect;
        GetWindowRect(hwnd, &wndRect);
        if (m_hWndForeground == NULL) {
            int width = wndRect.right - wndRect.left;
            int pos = int((wndRect.left + width / 2) / float(GetSystemMetrics(SM_CXFULLSCREEN)) * 100);
            if (std::abs(pos - int(m_options.WINPOS)) >= 5) {
                m_options.WINPOS = pos;
            }
        }
        else {
            int pos = int(float(wndRect.left - m_ForegroundWndRect.left) / float(m_ForegroundWndRect.right - m_ForegroundWndRect.left - (wndRect.right - wndRect.left)) * 100);
            pos = max(min(pos, 100), 0);
            if (std::abs(pos - int(m_options.WINPOS)) >= 5) {
                m_options.WINPOS = pos;
            }
            SetForegroundWindow(m_hWndForeground);
        }
        UpdatePosition();
    }
}

void CSprite::OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
    if (m_isMousePrees) {
        RECT winRect = { 0 };
        GetWindowRect(hwnd, &winRect);	//��ȡ���ڴ�С
        int cx = winRect.left + (x - m_mouseXY.x);
        int cy = winRect.top + (y - m_mouseXY.y);
        MoveWindow(hwnd, cx, cy, winRect.right - winRect.left, winRect.bottom - winRect.top, TRUE);	//�ƶ�����
    }
}

INT_PTR CALLBACK AboutDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_NOTIFY:
    {
        switch (((LPNMHDR)lParam)->code)
        {
        case NM_CLICK:
        case NM_RETURN:
        {
            PNMLINK pNMLink = (PNMLINK)lParam;
            LITEM item = pNMLink->item;
            HWND hLink = GetDlgItem(hDlg, IDC_SYSLINK);
            if ((((LPNMHDR)lParam)->hwndFrom == hLink) && (item.iLink == 0)) {
                ShellExecute(NULL, L"open", item.szUrl, NULL, NULL, SW_SHOW);
            }
        }
        return (INT_PTR)TRUE;
        }
        break;
    }
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

void CSprite::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id) {
    case ID_POPUP_SETTINGS:
        Hidden();
        extern HINSTANCE g_hInst;
        COptionsDlg::ShowDialog(g_hInst, hwnd, &m_options);
        Show();
        return;
    case ID_POPUP_ABOUT:
        extern HINSTANCE g_hInst;
        DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDialogProc);
        return;
    case ID_POPUP_QUIT:
    {
        std::vector<HWND> allSpriteWnd;
        EnumWindows(EnumWindowsProc, (LPARAM)&allSpriteWnd);
        for (auto iter = allSpriteWnd.cbegin(); iter != allSpriteWnd.cend(); iter++) {
            SendMessage(*iter, WM_CLOSE, 0, 0);
        }
    }
    return;
    case ID_POPUP_EXIT:
        DestroyWindow(hwnd);
        return;
    }
    if (m_MenuCommandHook != nullptr && m_CustomMenuIds.find((UINT)id) != m_CustomMenuIds.end()) {
        m_MenuCommandHook(m_popupMenu, (UINT)id);
        return;
    }
}

void CSprite::OnInitMenuPopup(HWND hWnd, HMENU hMenu, UINT item, BOOL fSystemMenu)
{
    if (m_popupMenu == hMenu) {
        // �����˵�ʱ��ȡ����ǰ��ʱ��
        KillTimer(hWnd, IDT_KEEP_TOP);
    }
}

void CSprite::OnUnInitMenuPopup(HWND hWnd, HMENU hMenu)
{
    if (m_popupMenu == hMenu) {
        // �����˵��ر�ʱ��ȡ����ǰ��ʱ��
        SetTimer(hWnd, IDT_KEEP_TOP, 1000, NULL);
    }
}

void CSprite::SetClickHook(void(*hook)())
{
    m_ClickHook = hook;
}

HMENU CSprite::AppendPopupMenu(LPCWSTR text)
{
    HMENU popup = CreatePopupMenu();
    if (InsertMenu(m_popupMenu, 2, MF_BYPOSITION | MF_POPUP, (UINT_PTR)popup, text)) {
        return popup;
    }
    return NULL;
}

BOOL CSprite::AppendChildMenu(HMENU hMenu, UINT identifier, LPCWSTR text)
{
    if (hMenu == NULL) {
        hMenu = m_popupMenu;
    }
    if (identifier == NULL) {
        return AppendMenu(hMenu, MF_SEPARATOR, NULL, NULL);
    }
    const bool is_in = m_CustomMenuIds.find(identifier) != m_CustomMenuIds.end();
    if (!is_in) {
        if (AppendMenu(hMenu, MF_STRING, identifier, text)) {
            m_CustomMenuIds.insert(identifier);
            return TRUE;
        }
    }
    return FALSE;
}

void CSprite::SetMenuCommandHook(void(*hook)(HMENU, UINT))
{
    m_MenuCommandHook = hook;
}

const OPTIONS* CSprite::GetOptions()
{
    return &m_options;
}
