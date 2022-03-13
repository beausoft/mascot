#include <Windows.h>
#include "../Sprite/ISprite.h"
#include "../Kaolla/StateMachine.h"
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

enum class StateEvent {
    EXIT = 0,
    CONTINUE = 1,
    CLICK = 2,
    PLAY_SLEEP = 3
};

ISprite* pSprite = NULL;
const ACTION* INIT_ACTION = NULL;
const ACTION* SHAKE_ACTION_A = NULL;
const ACTION* SHAKE_ACTION_B = NULL;
const ACTION* SHAKE_ACTION_C = NULL;
const ACTION* SLEEP_ACTION = NULL;
const ACTION* OTHER_ACTION = NULL;

StateMachine<StateEvent>* stateMachine = NULL;

VOID CALLBACK ActionTimer(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    if (idEvent == IDT_TRIGGER_ANIMATION) {
        stateMachine->doAction(StateEvent::CONTINUE);
    }
}

void MouseLeftButtonHook() {
    stateMachine->doAction(StateEvent::CLICK);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	FRAME USUAL = { IDB_USUAL , 0, 16 };
	FRAME INIT_FRAMES[] = { USUAL };
	INIT_ACTION = CreateAnimationAction(INIT_FRAMES, 1, 50, IDR_WAVE1, FALSE);

    FRAME SHAKE_1 = { IDB_SHAKE_1, 0, 16 };
    FRAME SHAKE_2 = { IDB_SHAKE_2, 0, 16 };
    FRAME SHAKE_3 = { IDB_SHAKE_3, 0, 16 };
    FRAME SHAKE_4 = { IDB_SHAKE_4, 0, 16 };
    FRAME SHAKE_5 = { IDB_SHAKE_5, 0, 16 };
    FRAME SHAKE_FRAMES_A[] = { USUAL, SHAKE_1, SHAKE_2, SHAKE_3, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_3, SHAKE_2, SHAKE_1, USUAL };
    SHAKE_ACTION_A = CreateAnimationAction(SHAKE_FRAMES_A, 17, 135, IDR_WAVE3, FALSE);

    FRAME SHAKE_FRAMES_B[] = { USUAL, SHAKE_1, SHAKE_2, SHAKE_3, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_3, SHAKE_2, SHAKE_1, USUAL };
    SHAKE_ACTION_B = CreateAnimationAction(SHAKE_FRAMES_B, 21, 135, IDR_WAVE2, FALSE);

    FRAME SHAKE_FRAMES_C[] = { USUAL, SHAKE_1, SHAKE_2, SHAKE_3, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_5, SHAKE_4, SHAKE_3, SHAKE_2, SHAKE_1, USUAL };
    SHAKE_ACTION_C = CreateAnimationAction(SHAKE_FRAMES_C, 25, 135, IDR_WAVE1, FALSE);

    FRAME SLEEP_1 = { IDB_SLEEP_1, 0, 24 };
    FRAME SLEEP_2 = { IDB_SLEEP_2, 0, 24 };
    FRAME SLEEP_3 = { IDB_SLEEP_3, 0, 24 };
    FRAME SLEEP_4 = { IDB_SLEEP_4, 0, 24 };
    FRAME SLEEP_FRAMES[] = { SLEEP_1 ,SLEEP_2, SLEEP_3, SLEEP_4, USUAL };
    SLEEP_ACTION = CreateAnimationAction(SLEEP_FRAMES, 5, 500, NULL, TRUE);

    OTHER_ACTION = CreateAnimationAction(INIT_FRAMES, 1, 50, IDR_WAVE4, FALSE);

    LPCWSTR appName = L"Mitsune";

    OPTIONS options = { 75, TRUE, TRUE, SELECTION::StartMenu };
    LoadOptions(hInstance, appName, &options);

    pSprite = CreateSprite(hInstance, appName, 96, 88, &options);
    pSprite->SetClickHook(MouseLeftButtonHook);
    pSprite->SetFrame(USUAL);
    pSprite->Show();

    stateMachine = new StateMachine<StateEvent>;
    // 初始状态
    State<StateEvent>* initState = new State<StateEvent>;
    initState->setEnter([]() { pSprite->PlayAnimation(INIT_ACTION); });
    // 终止状态
    State<StateEvent>* exitState = new State<StateEvent>;
    exitState->setEnter([]() { KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION); });
    // 随机设置触发时间
    State<StateEvent>* randomTimerState = new State<StateEvent>;
    randomTimerState->setEnter([]() { SetTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION, RandomRange(5000, 15000), ActionTimer); });
    // 随机触发动画
    State<StateEvent>* randomTriggerState = new State<StateEvent>;
    randomTriggerState->setEnter([]() { 
        KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
        float prob = GetProb();
        if (prob > 0.2 && prob < 0.3) {
            pSprite->PlayAnimation(OTHER_ACTION);
        }
        else if (prob > 0.5 && prob < 0.7) {
            pSprite->PlayAnimation(SHAKE_ACTION_B);
        }
        else if (prob > 0.8) {
            stateMachine->doAction(StateEvent::PLAY_SLEEP);
            return;
        }
        stateMachine->doAction(StateEvent::CONTINUE);
    });
    // 点击动画
    State<StateEvent>* clickState = new State<StateEvent>;
    clickState->setEnter([]() { 
        KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
        pSprite->PlayAnimation(SHAKE_ACTION_A);
        stateMachine->doAction(StateEvent::CONTINUE);
    });
    // 睡觉动画
    State<StateEvent>* sleepState = new State<StateEvent>;
    sleepState->setEnter([]() {
        KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
        pSprite->PlayAnimation(SLEEP_ACTION);
    });
    // 睡醒动画
    State<StateEvent>* wakeState = new State<StateEvent>;
    wakeState->setEnter([]() {
        KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
        pSprite->PlayAnimation(SHAKE_ACTION_C);
        stateMachine->doAction(StateEvent::CONTINUE);
    });

    initState->addTransition(StateEvent::CONTINUE, randomTimerState);
    initState->addTransition(StateEvent::EXIT, exitState);
    randomTimerState->addTransition(StateEvent::CONTINUE, randomTriggerState);
    randomTimerState->addTransition(StateEvent::EXIT, exitState);
    randomTimerState->addTransition(StateEvent::CLICK, clickState);
    randomTriggerState->addTransition(StateEvent::CONTINUE, randomTimerState);
    randomTriggerState->addTransition(StateEvent::EXIT, exitState);
    randomTriggerState->addTransition(StateEvent::PLAY_SLEEP, sleepState);
    clickState->addTransition(StateEvent::CONTINUE, randomTimerState);
    clickState->addTransition(StateEvent::EXIT, exitState);
    sleepState->addTransition(StateEvent::CONTINUE, wakeState);
    sleepState->addTransition(StateEvent::CLICK, wakeState);
    sleepState->addTransition(StateEvent::EXIT, exitState);
    wakeState->addTransition(StateEvent::CONTINUE, randomTimerState);
    wakeState->addTransition(StateEvent::EXIT, exitState);

    stateMachine->initState(initState);
    stateMachine->addState(exitState);
    stateMachine->addState(randomTimerState);
    stateMachine->addState(randomTriggerState);
    stateMachine->addState(clickState);
    stateMachine->addState(sleepState);
    stateMachine->addState(wakeState);
    stateMachine->start();
    stateMachine->doAction(StateEvent::CONTINUE);

    int ret = pSprite->EventLoop();
    const OPTIONS* lastOptions = pSprite->GetOptions();
    SaveOptions(hInstance, appName, lastOptions);

    stateMachine->doAction(StateEvent::EXIT);
    delete stateMachine;
    ReleaseSprite(pSprite);
    DeleteAnimationAction(INIT_ACTION);
    DeleteAnimationAction(SHAKE_ACTION_A);
    DeleteAnimationAction(SHAKE_ACTION_B);
    DeleteAnimationAction(SHAKE_ACTION_C);
    DeleteAnimationAction(SLEEP_ACTION);

    return ret;
}
