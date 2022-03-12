#include <Windows.h>
#include "../Sprite/ISprite.h"
#include "../Kaolla/StateMachine.h"
#include "resource.h"
#include <cstdlib>

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

float GetProb() {
    return (std::rand() % 100 + 1) / 100.f;
}

int RandomRange(int start, int end) {
    float prob = GetProb();
    int ret = int(prob * (end - start) + start);
    return ret;
}

enum class StateEvent {
    EXIT = 0,
    CONTINUE = 1,
    CLICK = 2,
    PLAY_SLEEP = 3
};

ISprite* pSprite = NULL;
const ACTION* INIT_ACTION = NULL;
const ACTION* ACTION_1 = NULL;
const ACTION* ACTION_2 = NULL;
const ACTION* ACTION_3 = NULL;
const ACTION* ACTION_4 = NULL;

StateMachine<StateEvent>* stateMachine = NULL;

VOID CALLBACK ActionTimer(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    //if (idEvent == IDT_TRIGGER_ANIMATION) {
    //    stateMachine->doAction(StateEvent::CONTINUE);
    //}
}

void MouseLeftButtonHook() {
    //stateMachine->doAction(StateEvent::CLICK);
    pSprite->PlayAnimation(ACTION_4);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    FRAME USUAL_1 = { IDB_USUAL_1 , 0, 8 };
    FRAME USUAL_2 = { IDB_USUAL_2 , 0, 8 };

    FRAME FRAME1_1 = { IDB_ACTION1_1 , 0, 8 };
    FRAME FRAME1_2 = { IDB_ACTION1_2 , 0, 8 };
    FRAME FRAME1_3 = { IDB_ACTION1_3 , 0, 8 };
    FRAME FRAME1_4 = { IDB_ACTION1_4 , 0, 8 };

    FRAME FRAME2_1 = { IDB_ACTION2_1 , 0, 8 };
    FRAME FRAME2_2 = { IDB_ACTION2_2 , 0, 8 };
    FRAME FRAME2_3 = { IDB_ACTION2_3 , 0, 8 };

    FRAME FRAME3_1 = { IDB_ACTION3_1 , 0, 8 };
    FRAME FRAME3_2 = { IDB_ACTION3_2 , 0, 8 };

    FRAME FRAME4_1 = { IDB_ACTION4_1 , 0, 8 };
    FRAME FRAME4_2 = { IDB_ACTION4_2 , 0, 8 };

    FRAME INIT_FRAMES[] = { USUAL_1 };
    INIT_ACTION = CreateAnimationAction(INIT_FRAMES, 1, 50, IDR_WAVE1, FALSE);
    FRAME FRAMES_1[] = { USUAL_1, FRAME1_1, FRAME1_2, FRAME1_3, FRAME1_4, FRAME1_3, FRAME1_2, FRAME1_3, FRAME1_4, FRAME1_3, FRAME1_2, FRAME1_3, FRAME1_4, FRAME1_3, FRAME1_2, FRAME1_3, FRAME1_4, FRAME1_3, FRAME1_2, FRAME1_3, FRAME1_4, FRAME1_3, FRAME1_2, FRAME1_1, USUAL_1 };
    ACTION_1 = CreateAnimationAction(FRAMES_1, 25, 130, IDR_WAVE2, FALSE);
    FRAME FRAMES_2[] = { FRAME2_1 ,FRAME2_2, FRAME2_3, FRAME2_2, FRAME2_1, FRAME2_2, FRAME2_3, FRAME2_2, FRAME2_1, FRAME2_2, FRAME2_3, FRAME2_2, FRAME2_1, FRAME2_2, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, USUAL_1 };
    ACTION_2 = CreateAnimationAction(FRAMES_2, 24, 130, IDR_WAVE2, FALSE);
    FRAME FRAMES_3[] = { FRAME4_1 , FRAME4_2, USUAL_1 };
    ACTION_3 = CreateAnimationAction(FRAMES_3, 3, 90, NULL, FALSE);

    FRAME FRAMES_4[] = { FRAME3_1 , FRAME3_2, USUAL_2 };
    ACTION_4 = CreateAnimationAction(FRAMES_4, 3, 90, NULL, FALSE);

    OPTIONS options = { 25, TRUE, TRUE, SELECTION::StartMenu };
    pSprite = CreateSprite(hInstance, L"Mitsune", 64, 88, &options);
    pSprite->SetClickHook(MouseLeftButtonHook);
    pSprite->SetFrame(USUAL_1);
    pSprite->Show();
    pSprite->PlayAnimation(INIT_ACTION);

    int ret = pSprite->EventLoop();

    delete stateMachine;

    return ret;

}
