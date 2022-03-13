#pragma once
#include <Windows.h>
#include "../Sprite/ISprite.h"

BOOL GetConfigPath(HINSTANCE hInstance, LPWSTR lpFilename, DWORD nSize) {
	memset(lpFilename, 0, nSize);
	if (GetModuleFileName(hInstance, lpFilename, MAX_PATH)) {
		for (int i = MAX_PATH - 1; i >= 0; i--) {
			if (lpFilename[i] == L'\\' || lpFilename[i] == L'/') {
				break;
			}
			lpFilename[i] = L'\0';
		}
		lstrcat(lpFilename, L"config.dat");
		return TRUE;
	}
	return FALSE;
}

void LoadOptions(HINSTANCE hInstance, LPCWSTR appName, OPTIONS* options) {
	WCHAR configFullPath[MAX_PATH] = { 0 };
	GetConfigPath(hInstance, configFullPath, MAX_PATH);
	options->WINPOS = GetPrivateProfileInt(appName, L"WINPOS", 30, configFullPath);
	options->SOUND = GetPrivateProfileInt(appName, L"UseSound", 1, configFullPath);
	options->ANIMATION = GetPrivateProfileInt(appName, L"ANIMATION", 1, configFullPath);
	options->selection = (SELECTION)GetPrivateProfileInt(appName, L"selection", 1, configFullPath);
}

BOOL WritePrivateProfileInt(_In_opt_ LPCWSTR lpAppName, _In_opt_ LPCWSTR lpKeyName, _In_opt_ INT value, _In_opt_ LPCWSTR lpFileName) {
	WCHAR strValue[32] = { 0 };
	wsprintf(strValue, L"%d", value);
	return WritePrivateProfileString(lpAppName, lpKeyName, strValue, lpFileName);
}

void SaveOptions(HINSTANCE hInstance, LPCWSTR appName, const OPTIONS* options) {
	WCHAR configFullPath[MAX_PATH] = { 0 };
	GetConfigPath(hInstance, configFullPath, MAX_PATH);
	WritePrivateProfileInt(appName, L"WINPOS", options->WINPOS, configFullPath);
	WritePrivateProfileInt(appName, L"UseSound", options->SOUND, configFullPath);
	WritePrivateProfileInt(appName, L"ANIMATION", options->ANIMATION, configFullPath);
	WritePrivateProfileInt(appName, L"selection", (INT)options->selection, configFullPath);
}