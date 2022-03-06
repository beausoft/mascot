#include "../Mascot/Sprite.h"
#include "resource.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    Sprite s(hInstance, L"Kaolla", 30, 30, 64, 96);
    s.SetShapeFromBitmap(IDB_USUAL);
    s.Show();

    UINT frames[] = { IDB_BLINK_1 ,IDB_BLINK_2 , IDB_USUAL };
    s.CreateAction(frames, 3, 100, IDR_WAVE1);

    /*
    Action blink;
    blink.AddFrame(IDB_BLINK_1);
    blink.AddFrame(IDB_BLINK_2);
    blink.AddFrame(IDB_USUAL);
    blink.SetSound(IDR_WAVE1);

    for (int i = 0; i < blink.GetFrameLength(); i++) {
        int a = blink.GetFrameLength();
        UINT rid = blink.GetFrame(i);
        int c = 0;
    }
    */

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
