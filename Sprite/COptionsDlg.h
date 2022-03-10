#pragma once
#include "ISprite.h"

class COptionsDlg
{
public:
	static BOOL ShowDialog(HINSTANCE hInstance, HWND hWndParent, OPTIONS* options);
private:
	static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	static void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	static void OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos);
};

