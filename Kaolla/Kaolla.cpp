#include "Sprite.h"
#include "resource.h"
#include "OptionsDlg.h"


Sprite *pS = NULL;

VOID CALLBACK test(HWND hWnd , UINT a, UINT_PTR b, DWORD c) {
    pS->PerformAnimation(0);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    Sprite s(hInstance, L"Kaolla", 30, 30, 64, 96);
    s.SetShapeFromBitmap(IDB_USUAL);
    s.Show();
    pS = &s;

    UINT blinkFrames[] = { IDB_BLINK_1 ,IDB_BLINK_2 , IDB_USUAL };
    int blink = s.CreateAction(blinkFrames, 3, 50, IDR_WAVE1);

    SetTimer(s.GetHandle(), 100002, 500, test);

    Options options;
    options.selection = ActiveWindow;
    options.SOUND = TRUE;
    options.ANIMATION = TRUE;
    OptionsDlg::ShowDialog(hInstance, s.GetHandle(), &options);


    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
