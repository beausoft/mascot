#include "Sprite.h"
#include "resource.h"
#include "OptionsDlg.h"
#include "hook.h"

constexpr auto IDT_TRIGGER_ANIMATION = 10001;

Sprite *sprite = NULL;
const ACTION* INIT_ACTION = NULL;
const ACTION* BLINK_ACTION = NULL;
const ACTION* LAUGH_ACTION_A = NULL;
const ACTION* LAUGH_ACTION_B = NULL;
const ACTION* HYPSOKINESIS_ACTION_1 = NULL;
const ACTION* HYPSOKINESIS_ACTION_2 = NULL;
const ACTION* HYPSOKINESIS_ACTION_3 = NULL;
const ACTION* CLICK_ACTION = NULL;
const ACTION* OTHER_ACTION = NULL;

VOID CALLBACK ActionTimer(HWND hWnd , UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    sprite->PlayAnimation(LAUGH_ACTION_B);
}

void MouseLeftButtonHook() {
    sprite->PlayAnimation(CLICK_ACTION);
}

void AnimationBeginHook() {}

void AnimationEndHook() {}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    FRAME USUAL = { IDB_USUAL ,0,42 };
    FRAME INIT_FRAMES[] = { USUAL };
    INIT_ACTION = CreateAnimationAction(INIT_FRAMES, 1, 50, IDR_WAVE1, FALSE);

    FRAME BLINK_1 = { IDB_BLINK_1 ,0,42 };
    FRAME BLINK_2 = { IDB_BLINK_2 ,0,42 };
    FRAME BIINK_FRAMES[] = { BLINK_1 ,BLINK_2 , USUAL };
    BLINK_ACTION = CreateAnimationAction(BIINK_FRAMES, 3, 50, NULL, FALSE);

    FRAME LAUGH_1 = { IDB_LAUGH_1 , 0 ,42 };
    FRAME LAUGH_2 = { IDB_LAUGH_2 , 0 ,42 };
    FRAME LAUGH_3 = { IDB_LAUGH_3 , 0 ,42 };
    FRAME LAUGH_4 = { IDB_LAUGH_4 , 0 ,42 };
    FRAME LAUGH_5 = { IDB_LAUGH_5 , 0 ,42 };
    FRAME LAUGH_6 = { IDB_LAUGH_6 , 0 ,42 };
    FRAME LAUGH_FRAMES[] = { LAUGH_1, LAUGH_2, LAUGH_3, LAUGH_4, LAUGH_5, LAUGH_6, LAUGH_1, LAUGH_2, LAUGH_3, LAUGH_4, LAUGH_5, LAUGH_6, LAUGH_1, LAUGH_2, LAUGH_3, LAUGH_4, LAUGH_5, LAUGH_6, LAUGH_1, USUAL };
    LAUGH_ACTION_A = CreateAnimationAction(LAUGH_FRAMES, 20, 100, IDR_WAVE1, FALSE);
    LAUGH_ACTION_B = CreateAnimationAction(LAUGH_FRAMES, 20, 100, IDR_WAVE2, FALSE);

    FRAME HYPSOKINESIS_1 = { IDB_HYPSOKINESIS_1 ,0, 42 };
    FRAME HYPSOKINESIS_2 = { IDB_HYPSOKINESIS_2 ,0, 42 };
    FRAME HYPSOKINESIS_3 = { IDB_HYPSOKINESIS_3 ,0, 42 };
    FRAME HYPSOKINESIS_4 = { IDB_HYPSOKINESIS_4 ,0, 42 };
    FRAME HYPSOKINESIS_5 = { IDB_HYPSOKINESIS_5 ,0, 42 };
    FRAME HYPSOKINESIS_6 = { IDB_HYPSOKINESIS_6 ,0, 42 };
    FRAME HYPSOKINESIS_7 = { IDB_HYPSOKINESIS_7 ,0, 42 };
    FRAME HYPSOKINESIS_FRAMES_1[] = { HYPSOKINESIS_1 ,HYPSOKINESIS_2, HYPSOKINESIS_3, HYPSOKINESIS_4, HYPSOKINESIS_5 };
    HYPSOKINESIS_ACTION_1 = CreateAnimationAction(HYPSOKINESIS_FRAMES_1, 5, 50, NULL, FALSE);
    FRAME HYPSOKINESIS_FRAMES_2[] = { HYPSOKINESIS_5 };
    HYPSOKINESIS_ACTION_2 = CreateAnimationAction(HYPSOKINESIS_FRAMES_2, 1, 50, IDR_WAVE3, FALSE);
    FRAME HYPSOKINESIS_FRAMES_3[] = { HYPSOKINESIS_5, HYPSOKINESIS_6, HYPSOKINESIS_7, USUAL };
    HYPSOKINESIS_ACTION_3 = CreateAnimationAction(HYPSOKINESIS_FRAMES_3, 4, 100, NULL, FALSE);

    FRAME CLICK_FRAMES[] = { USUAL };
    CLICK_ACTION = CreateAnimationAction(INIT_FRAMES, 1, 50, IDR_WAVE4, FALSE);
    FRAME OTHER_FRAMES[] = { USUAL };
    OTHER_ACTION = CreateAnimationAction(OTHER_FRAMES, 1, 50, IDR_WAVE5, FALSE);

    OPTIONS options;
    options.WINPOS = 30;
    options.selection = SELECTION::StartMenu;
    options.SOUND = TRUE;
    options.ANIMATION = TRUE;

    sprite = new Sprite(hInstance, L"Kaolla", 64, 96, &options);
    sprite->SetFrame(USUAL);
    sprite->Show();
    sprite->PlayAnimation(INIT_ACTION);

    SetTimer(sprite->GetHandle(), IDT_TRIGGER_ANIMATION, 8000, ActionTimer);

    int ret = sprite->EventLoop();
    delete sprite;
    DeleteAnimationAction(INIT_ACTION);
    DeleteAnimationAction(BLINK_ACTION);
    DeleteAnimationAction(LAUGH_ACTION_A);
    DeleteAnimationAction(LAUGH_ACTION_B);
    DeleteAnimationAction(HYPSOKINESIS_ACTION_1);
    DeleteAnimationAction(HYPSOKINESIS_ACTION_2);
    DeleteAnimationAction(HYPSOKINESIS_ACTION_3);
    DeleteAnimationAction(CLICK_ACTION);
    DeleteAnimationAction(OTHER_ACTION);

    return ret;
}
