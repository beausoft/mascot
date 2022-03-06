#pragma once
#include<Windows.h>
#include <windowsx.h>
#include <vector>

typedef struct tagACTION {
	UINT sound;
	int interval;
	int length;
	UINT frames[1];
}ACTION, * LPACTION;

struct AnimationStatus {
	BOOL running;
	int actionIndex;
	int frameIndex;
};

constexpr auto IDT_ANIMATION = 10005;

class Sprite
{
public:
	Sprite(HINSTANCE hInstance, LPCWSTR spriteName, INT x, INT y, INT nWidth, INT nHeight);
	~Sprite();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // ԭʼ���ڹ���
public:
	HWND GetHandle();  // ���ش��ڶ�����
	void Show();       // ��ʾ����
	void Hidden();     // ���ش���
	void SetShapeFromBitmap(UINT uIDBitmap);    // ����λͼ������״
	const int CreateAction(const UINT *frames, int framesLength, int interval, UINT sound);
	void PerformAnimation(UINT actionIndex);
private:
	void UpdateShape(HDC hdc);
private:
	BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
	void OnDestroy(HWND hWnd);
	void OnDisplayChange(HWND hwnd, UINT bitsPerPixel, UINT cxScreen, UINT cyScreen);
	UINT OnNCHitTest(HWND hwnd, int x, int y);
	void OnPaint(HWND hwnd);
	void OnActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized);
	void OnTimer(HWND hwnd, UINT id);
private:
	HWND m_hWnd = NULL;
	HINSTANCE m_hInstance = NULL;
	UINT m_uIDBitmap = NULL;
	std::vector<LPACTION> m_Actions;
	AnimationStatus m_AnimationStatus = { FALSE, 0, 0 };
};
