#pragma once
#include <Windows.h>

struct FRAME {
	int idBitmap;
	int offsetX;
	int offsetY;
};

struct ACTION {
	BOOL loop;
	UINT sound;
	int interval;
	int length;
	FRAME frames[1];
};

struct AnimationStatus {
	BOOL running;
	const ACTION* action;
	int frameIndex;
};

enum class SELECTION {
	Either = 0, StartMenu = 1, ActiveWindow = 2
};

struct OPTIONS {
	UINT WINPOS = 90;
	BOOL SOUND = FALSE;
	BOOL ANIMATION = FALSE;
	SELECTION selection = SELECTION::Either;
};

class ISprite
{
public:
	virtual HWND GetHandle() = 0;  // 返回窗口对象句柄
	virtual void Show() = 0;       // 显示窗口
	virtual void Hidden() = 0;     // 隐藏窗口
	virtual void SetFrame(FRAME pFrame) = 0;
	virtual int EventLoop() = 0;
	virtual void PlayAnimation(const ACTION* pAction) = 0;
	virtual void StopAnimation() = 0;
	virtual void SetClickHook(void (*hook)()) = 0;
	virtual HMENU AppendPopupMenu(LPCWSTR text) = 0;
	virtual BOOL AppendChildMenu(HMENU hMenu, UINT identifier, LPCWSTR text) = 0;
	virtual void SetMenuCommandHook(void (*menuCommandHook)(HMENU, UINT)) = 0;
};

#define EXPORT_API __declspec(dllexport)

extern "C" {
	EXPORT_API ISprite* CreateSprite(HINSTANCE hInstance, LPCWSTR spriteName, INT nWidth, INT nHeight, const OPTIONS* options);
	EXPORT_API void ReleaseSprite(ISprite* pSprite);
}
