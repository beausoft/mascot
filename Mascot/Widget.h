#pragma once
#include<Windows.h>
#include <windowsx.h>

class Widget
{
public:
	Widget(HINSTANCE hInstance, LPCWSTR name, INT x, INT y, INT nWidth, INT nHeight);
	~Widget();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // ԭʼ���ڹ���
public:
	HWND GetHandle();  // ���ش��ڶ�����
	void Show();
	void Hide();
	void SetShapeFromBitmap(UINT uIDBitmap);
private:
	void UpdateShape(HDC hdc);
private:
	BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
	void OnDestroy(HWND hWnd);
	void OnDisplayChange(HWND hwnd, UINT bitsPerPixel, UINT cxScreen, UINT cyScreen);
	UINT OnNCHitTest(HWND hwnd, int x, int y);
	void OnPaint(HWND hwnd);
private:
	HWND m_hWnd = NULL;
	HINSTANCE m_hInstance = NULL;
	UINT m_uIDBitmap = NULL;
};
