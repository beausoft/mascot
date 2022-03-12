#include <Windows.h>
#include "../Sprite/ISprite.h"
#include "resource.h"
#include <cstdlib>

float GetProb() {
    return (std::rand() % 100 + 1) / 100.f;
}

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
const ACTION* INIT_ACTION = NULL;
const ACTION* BLINK_ACTION = NULL;
const ACTION* INCLINATION_ACTION = NULL;
const ACTION* ACTION_1 = NULL;
const ACTION* ACTION_2 = NULL;
const ACTION* ACTION_3 = NULL;

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
    FRAME USUAL = { IDB_USUAL , 0, 21 };
	FRAME INIT_FRAMES[] = { USUAL };
	INIT_ACTION = CreateAnimationAction(INIT_FRAMES, 1, 50, IDR_WAVE1, FALSE);

    FRAME BLINK_1 = { IDB_BLINK_1, 0, 21 };
    FRAME BLINK_2 = { IDB_BLINK_2, 0, 21 };
    FRAME BIINK_FRAMES[] = { BLINK_1 ,BLINK_2 , USUAL };
    BLINK_ACTION = CreateAnimationAction(BIINK_FRAMES, 3, 50, NULL, FALSE);

    FRAME INCLINATION_1 = { IDB_INCLINATION_1, 0, 21 };
    FRAME INCLINATION_2 = { IDB_INCLINATION_2, 0, 21 };
    FRAME INCLINATION_FRAMES[] = { INCLINATION_1, INCLINATION_1, INCLINATION_2, INCLINATION_2, USUAL };
    INCLINATION_ACTION = CreateAnimationAction(INCLINATION_FRAMES, 5, 80, IDR_WAVE3, FALSE);

    ACTION_1 = CreateAnimationAction(&USUAL, 1, 80, IDR_WAVE2, FALSE);
    ACTION_2 = CreateAnimationAction(&USUAL, 1, 80, IDR_WAVE4, FALSE);
    ACTION_3 = CreateAnimationAction(&USUAL, 1, 80, IDR_WAVE5, FALSE);

    OPTIONS options = { 50, TRUE, TRUE, SELECTION::StartMenu };

	pSprite = CreateSprite(hInstance, L"Mei", 80, 104, &options);
    pSprite->SetFrame(USUAL);
	pSprite->Show();
    pSprite->PlayAnimation(INIT_ACTION);
    pSprite->SetClickHook([]() {
        KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
        pSprite->PlayAnimation(INCLINATION_ACTION);
        SetTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION, 8000, ActionTimer);
    });

    SetTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION, 8000, ActionTimer);

	int ret = pSprite->EventLoop();

    KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);

	ReleaseSprite(pSprite);
    DeleteAnimationAction(INIT_ACTION);
    DeleteAnimationAction(BLINK_ACTION);
    DeleteAnimationAction(INCLINATION_ACTION);
    DeleteAnimationAction(ACTION_1);
    DeleteAnimationAction(ACTION_2);
    DeleteAnimationAction(ACTION_3);
	return ret;
}