#pragma once
#include<Windows.h>
#include "OptionsDlg.h"
#include "Animation.h"

constexpr auto IDT_ANIMATION = 10005;
constexpr auto IDT_WINDOW_DETECTION = 10006;

class Sprite
{
public:
	Sprite(HINSTANCE hInstance, LPCWSTR spriteName, INT nWidth, INT nHeight, const OPTIONS* options);
	~Sprite();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 原始窗口过程
public:
	HWND GetHandle();  // 返回窗口对象句柄
	void Show();       // 显示窗口
	void Hidden();     // 隐藏窗口
	void SetFrame(FRAME pFrame);
	int EventLoop();
	void PlayAnimation(const ACTION* pAction);
	void StopAnimation();
private:
	void UpdateShape(HDC hdc);
	void UpdatePosition();
	void Set_hWndForeground(HWND hWndForeground);
private:
	BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
	void OnClose(HWND hwnd);
	void OnDestroy(HWND hWnd);
	void OnDisplayChange(HWND hwnd, UINT bitsPerPixel, UINT cxScreen, UINT cyScreen);
	UINT OnNCHitTest(HWND hwnd, int x, int y);
	void OnPaint(HWND hwnd);
	void OnActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized);
	void OnTimer(HWND hwnd, UINT id);
	void OnRButtonUp(HWND hwnd, int x, int y, UINT flags);
	void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
	void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
	void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
	void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
private:
	HWND m_hWnd = NULL;
	HINSTANCE m_hInstance = NULL;
	BOOL m_isMousePrees = FALSE;
	POINT m_mouseXY = { 0 };
	HMENU m_popupMenu = NULL;
	OPTIONS m_options;
	FRAME m_frame = { 0 };
	AnimationStatus m_AnimationStatus = { FALSE, NULL, 0 };
	HWND m_hWndForeground = NULL;
	RECT m_ForegroundWndRect = { 0 };
};
