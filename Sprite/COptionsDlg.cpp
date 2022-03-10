#include "COptionsDlg.h"
#include "resource.h"
#include <windowsx.h>
#include <Commctrl.h>

BOOL COptionsDlg::ShowDialog(HINSTANCE hInstance, HWND hWndParent, OPTIONS* options)
{
	INT_PTR ret = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_OPTIONSBOX), hWndParent, DialogProc, (LPARAM)options);
	return ret != -1;
}

INT_PTR COptionsDlg::DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		HANDLE_MSG(hDlg, WM_INITDIALOG, OnInitDialog);
		HANDLE_MSG(hDlg, WM_COMMAND, OnCommand);
		HANDLE_MSG(hDlg, WM_HSCROLL, OnHScroll);
	}
	return (INT_PTR)FALSE;
}

BOOL COptionsDlg::OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	OPTIONS* pOptions = (OPTIONS*)lParam;
	HWND hWndWidget = NULL;

	// https://docs.microsoft.com/en-us/windows/win32/controls/tbm-getpos
	SendMessage(GetDlgItem(hwnd, IDC_SWINPOS), TBM_SETRANGE, (WPARAM)FALSE, (LPARAM)MAKELONG(0, 100));
	SendMessage(GetDlgItem(hwnd, IDC_SWINPOS), TBM_SETPOS, (WPARAM)TRUE, pOptions->WINPOS);

	WCHAR szText[16] = { 0 };
	wsprintf(szText, L"%d", pOptions->WINPOS);
	Edit_SetText(GetDlgItem(hwnd, IDC_EWNDPOS), szText);

	int selectedRadio;
	switch (pOptions->selection) {
	case SELECTION::Either:
		selectedRadio = IDC_REITHER;
		break;
	case SELECTION::StartMenu:
		selectedRadio = IDC_RSTARTMENU;
		break;
	case SELECTION::ActiveWindow:
		selectedRadio = IDC_RACTIVEWINDOW;
		break;
	default:
		selectedRadio = IDC_REITHER;
		break;
	}
	CheckRadioButton(hwnd, IDC_REITHER, IDC_RACTIVEWINDOW, selectedRadio);

	// https://docs.microsoft.com/en-us/windows/win32/controls/bm-setcheck
	Button_SetCheck(GetDlgItem(hwnd, IDC_CSOUND), pOptions->SOUND);
	Button_SetCheck(GetDlgItem(hwnd, IDC_CANIMATION), pOptions->ANIMATION);

	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pOptions);
	return TRUE;
}

void COptionsDlg::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id) {
	case IDOK:
	{
		OPTIONS* pOptions = (OPTIONS*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		pOptions->WINPOS = (UINT)SendMessage(GetDlgItem(hwnd, IDC_SWINPOS), TBM_GETPOS, 0, 0);

		if (IsDlgButtonChecked(hwnd, IDC_REITHER)) {
			pOptions->selection = SELECTION::Either;
		}
		else if (IsDlgButtonChecked(hwnd, IDC_RSTARTMENU)) {
			pOptions->selection = SELECTION::StartMenu;
		}
		else if (IsDlgButtonChecked(hwnd, IDC_RACTIVEWINDOW)) {
			pOptions->selection = SELECTION::ActiveWindow;
		}

		pOptions->SOUND = IsDlgButtonChecked(hwnd, IDC_CSOUND);
		pOptions->ANIMATION = IsDlgButtonChecked(hwnd, IDC_CANIMATION);

	}
	case IDCANCEL:
		EndDialog(hwnd, id);
		break;
	case IDC_EWNDPOS:
		if (codeNotify == EN_CHANGE) {
			BOOL ret;
			int pos = (int)GetDlgItemInt(hwnd, IDC_EWNDPOS, &ret, FALSE);
			if (ret && pos >= 0 && pos <= 100) {
				SendMessage(GetDlgItem(hwnd, IDC_SWINPOS), TBM_SETPOS, (WPARAM)TRUE, pos);
			}
			else {
				MessageBox(hwnd, L"请输入0到100之间的整数", L"提示", MB_OK | MB_ICONWARNING);
			}
		}
		break;
	}
}

void COptionsDlg::OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
{
	if (code == SB_THUMBTRACK && hwndCtl == GetDlgItem(hwnd, IDC_SWINPOS)) {
		SetDlgItemInt(hwnd, IDC_EWNDPOS, pos, FALSE);   // https://docs.microsoft.com/en-us/windows/win32/controls/edit-controls-text-operations
	}
}
