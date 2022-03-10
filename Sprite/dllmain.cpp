#include <windows.h>

extern HINSTANCE g_hInst = NULL;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
        g_hInst = hModule;
        break;
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        g_hInst = NULL;
        break;
    }
    return TRUE;
}

