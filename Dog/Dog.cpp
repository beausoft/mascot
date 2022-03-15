#include <Windows.h>
#include "../Sprite/ISprite.h"
#include "resource.h"
#include "../Kaolla/random.h"
#include "../Mei/Config.h"

constexpr auto IDT_TRIGGER_ANIMATION = 10001;

const ACTION* CreateAnimationAction(const FRAME* frames, int framesLength, int interval, UINT sound, BOOL loop)
{
    ACTION* action = (ACTION*)malloc(sizeof(ACTION) + framesLength * sizeof(FRAME));
    // 判断内存是否申请成功
    if (action == NULL) return NULL;
    action->loop = loop;
    action->sound = sound;
    action->interval = interval;
    action->length = framesLength;
    memcpy(action->frames, frames, framesLength * sizeof(FRAME));
    return action;
}

void DeleteAnimationAction(const ACTION* pAction)
{
    free((ACTION*)pAction);
}

ISprite* pSprite = NULL;
const ACTION* ACTION_1 = NULL;
const ACTION* ACTION_2 = NULL;
const ACTION* ACTION_3 = NULL;
const ACTION* BLINK_ACTION = NULL;

VOID CALLBACK ActionTimer(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    if (idEvent == IDT_TRIGGER_ANIMATION) {
        if (pSprite != NULL) {
            if (GetProb() <= 0.8f) {
                pSprite->PlayAnimation(BLINK_ACTION);
            }
            else {
                float prob = GetProb();
                if (prob < 0.3) {
                    pSprite->PlayAnimation(ACTION_1);
                }
                else if (prob < 0.6) {
                    pSprite->PlayAnimation(ACTION_2);
                }
                else if (prob < 0.9) {
                    pSprite->PlayAnimation(ACTION_3);
                }
            }
        }
    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    FRAME FRAME_1 = { IDB_BITMAP1 , 0, 0 };
    FRAME FRAME_2 = { IDB_BITMAP2 , 0, 0 };
    FRAME FRAME_3 = { IDB_BITMAP3 , 0, 0 };

    FRAME INIT_FRAMES[] = { FRAME_1 };
    ACTION_1 = CreateAnimationAction(INIT_FRAMES, 1, 50, IDR_WAVE1, FALSE);
    ACTION_2 = CreateAnimationAction(INIT_FRAMES, 1, 50, IDR_WAVE2, FALSE);
    ACTION_3 = CreateAnimationAction(INIT_FRAMES, 1, 50, IDR_WAVE3, FALSE);

    FRAME BIINK_FRAMES[] = { FRAME_1, FRAME_2 ,FRAME_3, FRAME_2, FRAME_3, FRAME_2, FRAME_3, FRAME_1 };
    BLINK_ACTION = CreateAnimationAction(BIINK_FRAMES, 8, 130, NULL, FALSE);

    LPCWSTR appName = L"Dog";
    OPTIONS options = { 50, TRUE, TRUE, SELECTION::StartMenu };
    LoadOptions(hInstance, appName, &options);

    pSprite = CreateSprite(hInstance, appName, 74, 94, &options);
    pSprite->SetFrame(FRAME_1);
    pSprite->Show();
    pSprite->PlayAnimation(ACTION_1);
    pSprite->SetClickHook([]() {
        KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
        pSprite->PlayAnimation(ACTION_2);
        SetTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION, 8000, ActionTimer);
    });

    SetTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION, 8000, ActionTimer);

    int ret = pSprite->EventLoop();
    const OPTIONS* lastOptions = pSprite->GetOptions();
    SaveOptions(hInstance, appName, lastOptions);

    KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);

    ReleaseSprite(pSprite);
    DeleteAnimationAction(ACTION_1);
    DeleteAnimationAction(ACTION_2);
    DeleteAnimationAction(ACTION_3);
    return ret;
}
