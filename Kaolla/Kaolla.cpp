#include "Sprite.h"
#include "resource.h"
#include "OptionsDlg.h"


Sprite *sprite = NULL;

VOID CALLBACK test(HWND hWnd , UINT a, UINT_PTR b, DWORD c) {
    sprite->StopAnimation();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    OPTIONS options;
    options.selection = SELECTION::StartMenu;
    options.SOUND = TRUE;
    options.ANIMATION = TRUE;

    sprite = new Sprite(hInstance, L"Kaolla", 64, 96, &options);
    FRAME USUAL = { IDB_USUAL ,0,40 };
    FRAME BLINK_1 = { IDB_BLINK_1 ,0,40 };
    FRAME BLINK_2 = { IDB_BLINK_2 ,0,40 };
    FRAME blinkFrames[] = { BLINK_1 ,BLINK_2 , USUAL };

    sprite->SetFrame(USUAL);
    sprite->Show();
    
    const ACTION* blink = CreateAnimationAction(blinkFrames, 3, 100, IDR_WAVE1, TRUE);
    //DeleteAnimationAction(blink);
    sprite->PlayAnimation(blink);



    //
    //s.PlayAnimation(blink);

    SetTimer(sprite->GetHandle(), 100002, 5000, test);

    return sprite->EventLoop();
}
