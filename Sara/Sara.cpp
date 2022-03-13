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
    HOSTATE = 3   // 切换状态事件
};

ISprite* pSprite = NULL;
const ACTION* ACTIONA_INIT = NULL;
const ACTION* ACTIONA_1 = NULL;
const ACTION* ACTIONA_2 = NULL;
const ACTION* ACTIONA_3 = NULL;   // 眨眼
const ACTION* ACTIONA_4 = NULL;

const ACTION* ACTIONB_INIT = NULL;
const ACTION* ACTIONB_1 = NULL;   // 眨眼
const ACTION* ACTIONB_2 = NULL;
const ACTION* ACTIONB_3 = NULL;



StateMachine<StateEvent>* stateMachine = NULL;

VOID CALLBACK ActionTimer(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    if (idEvent == IDT_TRIGGER_ANIMATION) {
        stateMachine->doAction(StateEvent::CONTINUE);
    }
}

void MouseLeftButtonHook() {
    stateMachine->doAction(StateEvent::CLICK);
    //pSprite->PlayAnimation(ACTIONB_1);
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

    FRAME FRAME5 = { IDB_ACTION5 , 0, 8 };

    FRAME INIT_FRAMES[] = { USUAL_1 };
    ACTIONA_INIT = CreateAnimationAction(INIT_FRAMES, 1, 50, IDR_WAVE1, FALSE);
    FRAME FRAMESA_1[] = { USUAL_1, FRAME1_1, FRAME1_2, FRAME1_3, FRAME1_4, FRAME1_3, FRAME1_2, FRAME1_3, FRAME1_4, FRAME1_3, FRAME1_2, FRAME1_3, FRAME1_4, FRAME1_3, FRAME1_2, FRAME1_3, FRAME1_4, FRAME1_3, FRAME1_2, FRAME1_3, FRAME1_4, FRAME1_3, FRAME1_2, FRAME1_1, USUAL_1 };
    ACTIONA_1 = CreateAnimationAction(FRAMESA_1, 25, 130, IDR_WAVE2, FALSE);
    FRAME FRAMESA_2[] = { FRAME2_1 ,FRAME2_2, FRAME2_3, FRAME2_2, FRAME2_1, FRAME2_2, FRAME2_3, FRAME2_2, FRAME2_1, FRAME2_2, FRAME2_3, FRAME2_2, FRAME2_1, FRAME2_2, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, USUAL_1 };
    ACTIONA_2 = CreateAnimationAction(FRAMESA_2, 24, 130, IDR_WAVE2, FALSE);
    FRAME FRAMESA_3[] = { FRAME4_1 , FRAME4_2, USUAL_1 };
    ACTIONA_3 = CreateAnimationAction(FRAMESA_3, 3, 90, NULL, FALSE);
    FRAME FRAMESA_4[] = { FRAME2_1 ,FRAME2_2, FRAME2_3, FRAME2_2, FRAME2_1, FRAME2_2, FRAME2_3, FRAME2_2, FRAME2_1, FRAME2_2, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, FRAME2_3, USUAL_1 };
    ACTIONA_4 = CreateAnimationAction(FRAMESA_4, 18, 130, IDR_WAVE3, FALSE);

    FRAME FRAMESB_1[] = { FRAME3_1 , FRAME3_2, USUAL_2 };
    ACTIONB_1 = CreateAnimationAction(FRAMESB_1, 3, 90, NULL, FALSE);
    FRAME FRAMESB_2[] = { FRAME5, USUAL_2 };
    ACTIONB_2 = CreateAnimationAction(FRAMESB_2, 2, 5000, IDR_WAVE4, FALSE);
    FRAME FRAMESB_3[] = { FRAME5, USUAL_2 };
    ACTIONB_3 = CreateAnimationAction(FRAMESB_3, 2, 2000, IDR_WAVE5, FALSE);
    FRAME FRAMESB_INIT[] = { USUAL_2 };
    ACTIONB_INIT = CreateAnimationAction(FRAMESB_INIT, 1, 50, NULL, FALSE);
    
    stateMachine = new StateMachine<StateEvent>;
    // 初始状态
    State<StateEvent>* initState = new State<StateEvent>;
    initState->setEnter([]() { pSprite->PlayAnimation(ACTIONA_INIT); });
    // 终止状态
    State<StateEvent>* exitState = new State<StateEvent>;
    exitState->setEnter([]() { KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION); });
    // 站立模式-随机设置触发时间
    State<StateEvent>* randomTimerAState = new State<StateEvent>;
    randomTimerAState->setEnter([]() { SetTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION, RandomRange(5000, 10000), ActionTimer); });
    // 站立模式-随机触发动画
    State<StateEvent>* randomTriggerAState = new State<StateEvent>;
    randomTriggerAState->setEnter([]() {
        KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
        if (GetProb() <= 0.75f) {
            pSprite->PlayAnimation(ACTIONA_3);
        }
        else {
            float prob = GetProb();
            if (prob <= 0.25f) {
                pSprite->PlayAnimation(ACTIONA_1);
            }
            else if (prob <= 0.5f) {
                pSprite->PlayAnimation(ACTIONA_2);
            }
            else if (prob <= 0.75f) {
                pSprite->PlayAnimation(ACTIONA_4);
            }
            else {
                stateMachine->doAction(StateEvent::HOSTATE);
                return;
            }
        }
        stateMachine->doAction(StateEvent::CONTINUE);
    });
    // 点击动画
    State<StateEvent>* clickState = new State<StateEvent>;
    clickState->setEnter([]() { 
        KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
        pSprite->PlayAnimation(ACTIONA_1);
        stateMachine->doAction(StateEvent::CONTINUE);
    });
    // 切换到趴下状态
    State<StateEvent>* switchToBState = new State<StateEvent>;
    switchToBState->setEnter([]() {
        KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
        pSprite->PlayAnimation(ACTIONB_INIT);
        stateMachine->doAction(StateEvent::CONTINUE);
    });
    // 趴下模式-随机设置触发时间
    State<StateEvent>* randomTimerBState = new State<StateEvent>;
    randomTimerBState->setEnter([]() { SetTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION, RandomRange(5000, 10000), ActionTimer); });
    // 趴下模式-随机触发动画
    State<StateEvent>* randomTriggerBState = new State<StateEvent>;
    randomTriggerBState->setEnter([]() {
        KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
        if (GetProb() <= 0.75f) {
            pSprite->PlayAnimation(ACTIONB_1);
        }
        else {
            float prob = GetProb();
            if (prob <= 0.35f) {
                pSprite->PlayAnimation(ACTIONB_2);
            }
            else if (prob <= 0.7f) {
                pSprite->PlayAnimation(ACTIONB_3);
            }
            else {
                stateMachine->doAction(StateEvent::HOSTATE);
                return;
            }
        }
        stateMachine->doAction(StateEvent::CONTINUE);
    });
    // 切换到趴下状态
    State<StateEvent>* switchToAState = new State<StateEvent>;
    switchToAState->setEnter([]() {
        KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
        pSprite->PlayAnimation(ACTIONA_INIT);
        stateMachine->doAction(StateEvent::CONTINUE);
    });


    initState->addTransition(StateEvent::CONTINUE, randomTimerAState);
    initState->addTransition(StateEvent::EXIT, exitState);
    randomTimerAState->addTransition(StateEvent::CONTINUE, randomTriggerAState);
    randomTimerAState->addTransition(StateEvent::CLICK, clickState);
    randomTimerAState->addTransition(StateEvent::EXIT, exitState);
    clickState->addTransition(StateEvent::CONTINUE, randomTimerAState);
    clickState->addTransition(StateEvent::EXIT, exitState);
    randomTriggerAState->addTransition(StateEvent::CONTINUE, randomTimerAState);
    randomTriggerAState->addTransition(StateEvent::EXIT, exitState);
    randomTriggerAState->addTransition(StateEvent::HOSTATE, switchToBState);
    switchToBState->addTransition(StateEvent::CONTINUE, randomTimerBState);
    switchToBState->addTransition(StateEvent::EXIT, exitState);
    randomTimerBState->addTransition(StateEvent::CONTINUE, randomTriggerBState);
    randomTimerBState->addTransition(StateEvent::CLICK, clickState);   // 点击执行站立模式的点击
    randomTimerBState->addTransition(StateEvent::EXIT, exitState);
    randomTriggerBState->addTransition(StateEvent::CONTINUE, randomTimerBState);
    randomTriggerBState->addTransition(StateEvent::EXIT, exitState);
    randomTriggerBState->addTransition(StateEvent::HOSTATE, switchToAState);
    switchToAState->addTransition(StateEvent::CONTINUE, randomTimerAState);
    switchToAState->addTransition(StateEvent::EXIT, exitState);


    stateMachine->initState(initState);
    stateMachine->addState(exitState);
    stateMachine->addState(randomTimerAState);
    stateMachine->addState(clickState);
    stateMachine->addState(randomTriggerAState);
    stateMachine->addState(switchToBState);
    stateMachine->addState(randomTimerBState);
    stateMachine->addState(randomTriggerBState);
    stateMachine->addState(switchToAState);

    LPCWSTR appName = L"Sara";

    OPTIONS options = { 25, TRUE, TRUE, SELECTION::StartMenu };
    LoadOptions(hInstance, appName, &options);

    pSprite = CreateSprite(hInstance, appName, 64, 88, &options);
    pSprite->SetClickHook(MouseLeftButtonHook);
    pSprite->SetFrame(USUAL_1);
    pSprite->Show();
    
    stateMachine->start();
    stateMachine->doAction(StateEvent::CONTINUE);

    int ret = pSprite->EventLoop();
    const OPTIONS* lastOptions = pSprite->GetOptions();
    SaveOptions(hInstance, appName, lastOptions);

    stateMachine->doAction(StateEvent::EXIT);
    delete stateMachine;
    ReleaseSprite(pSprite);
    DeleteAnimationAction(ACTIONA_INIT);
    DeleteAnimationAction(ACTIONA_1);
    DeleteAnimationAction(ACTIONA_2);
    DeleteAnimationAction(ACTIONA_3);
    DeleteAnimationAction(ACTIONA_4);
    DeleteAnimationAction(ACTIONB_INIT);
    DeleteAnimationAction(ACTIONB_1);
    DeleteAnimationAction(ACTIONB_2);
    DeleteAnimationAction(ACTIONB_3);
    return ret;

}
