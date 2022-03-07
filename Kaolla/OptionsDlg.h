#pragma once
#include <Windows.h>

enum class SELECTION {
	Either = 0, StartMenu = 1, ActiveWindow = 2
};

struct OPTIONS {
	UINT WINPOS = 90;
	BOOL SOUND = FALSE;
	BOOL ANIMATION = FALSE;
	SELECTION selection = SELECTION::Either;
};

class OptionsDlg
{
public:
	static BOOL ShowDialog(HINSTANCE hInstance, HWND hWndParent, OPTIONS* options);
private:
	static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	static void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	static void OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos);
};

