#include "Sprite.h"
#include "resource.h"
#include "OptionsDlg.h"
#include "StateMachine.h"
#include "random.h"

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

enum class StateEvent {
    EXIT = 0,
    CONTINUE = 1,
    PLAY_HYPSOKINESIS = 2,
    CLICK = 3
};
StateMachine<StateEvent>* stateMachine = NULL;

VOID CALLBACK ActionTimer(HWND hWnd , UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    if (idEvent == IDT_TRIGGER_ANIMATION) {
        stateMachine->doAction(StateEvent::CONTINUE);
    }
}

void MouseLeftButtonHook() {
    stateMachine->doAction(StateEvent::CLICK);
}

BOOL GetConfigPath(HINSTANCE hInstance, LPWSTR lpFilename, DWORD nSize) {
    memset(lpFilename, 0, nSize);
    if (GetModuleFileName(hInstance, lpFilename, MAX_PATH)) {
        for (int i = MAX_PATH - 1; i >= 0; i--) {
            if (lpFilename[i] == L'\\' || lpFilename[i] == L'/') {
                break;
            }
            lpFilename[i] = L'\0';
        }
        lstrcat(lpFilename, L"config.dat");
        return TRUE;
    }
    return FALSE;
}

void LoadOptions(HINSTANCE hInstance, LPCWSTR appName, OPTIONS *options) {
    WCHAR configFullPath[MAX_PATH];
    GetConfigPath(hInstance, configFullPath, MAX_PATH);
    options->WINPOS = GetPrivateProfileInt(appName, L"WINPOS", 30, configFullPath);
    options->SOUND = GetPrivateProfileInt(appName, L"UseSound", 1, configFullPath);
    options->ANIMATION = GetPrivateProfileInt(appName, L"ANIMATION", 1, configFullPath);
    options->selection = (SELECTION)GetPrivateProfileInt(appName, L"selection", 1, configFullPath);
}

BOOL WritePrivateProfileInt(_In_opt_ LPCWSTR lpAppName, _In_opt_ LPCWSTR lpKeyName, _In_opt_ INT value, _In_opt_ LPCWSTR lpFileName) {
    WCHAR strValue[32] = { 0 };
    wsprintf(strValue, L"%d", value);
    return WritePrivateProfileString(lpAppName, lpKeyName, strValue, lpFileName);
}

void SaveOptions(HINSTANCE hInstance, LPCWSTR appName, const OPTIONS* options) {
    WCHAR configFullPath[MAX_PATH];
    GetConfigPath(hInstance, configFullPath, MAX_PATH);
    WritePrivateProfileInt(appName, L"WINPOS", options->WINPOS, configFullPath);
    WritePrivateProfileInt(appName, L"UseSound", options->SOUND, configFullPath);
    WritePrivateProfileInt(appName, L"ANIMATION", options->ANIMATION, configFullPath);
    WritePrivateProfileInt(appName, L"selection", (INT)options->selection, configFullPath);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    FRAME USUAL = { IDB_USUAL ,0,13 };
    FRAME INIT_FRAMES[] = { USUAL };
    INIT_ACTION = CreateAnimationAction(INIT_FRAMES, 1, 50, IDR_WAVE1, FALSE);

    FRAME BLINK_1 = { IDB_BLINK_1 ,0,13 };
    FRAME BLINK_2 = { IDB_BLINK_2 ,0,13 };
    FRAME BIINK_FRAMES[] = { BLINK_1 ,BLINK_2 , USUAL };
    BLINK_ACTION = CreateAnimationAction(BIINK_FRAMES, 3, 50, NULL, FALSE);

    FRAME LAUGH_1 = { IDB_LAUGH_1 , 0 ,13 };
    FRAME LAUGH_2 = { IDB_LAUGH_2 , 0 ,13 };
    FRAME LAUGH_3 = { IDB_LAUGH_3 , 0 ,13 };
    FRAME LAUGH_4 = { IDB_LAUGH_4 , 0 ,13 };
    FRAME LAUGH_5 = { IDB_LAUGH_5 , 0 ,13 };
    FRAME LAUGH_6 = { IDB_LAUGH_6 , 0 ,13 };
    FRAME LAUGH_FRAMES_1[] = { LAUGH_1, LAUGH_2, LAUGH_3, LAUGH_4, LAUGH_5, LAUGH_6, LAUGH_1, LAUGH_2, LAUGH_3, LAUGH_4, LAUGH_5, LAUGH_6, LAUGH_1, LAUGH_2, LAUGH_3, LAUGH_4, LAUGH_5, LAUGH_6, LAUGH_1, LAUGH_2, LAUGH_3, LAUGH_4, LAUGH_5, LAUGH_6, LAUGH_1, USUAL };
    LAUGH_ACTION_A = CreateAnimationAction(LAUGH_FRAMES_1, 26, 100, IDR_WAVE1, FALSE);
    FRAME LAUGH_FRAMES_2[] = { LAUGH_1, LAUGH_2, LAUGH_3, LAUGH_4, LAUGH_5, LAUGH_6, LAUGH_1, LAUGH_2, LAUGH_3, LAUGH_4, LAUGH_5, LAUGH_6, LAUGH_1, LAUGH_2, LAUGH_3, LAUGH_4, LAUGH_5, LAUGH_6, LAUGH_1, USUAL };
    LAUGH_ACTION_B = CreateAnimationAction(LAUGH_FRAMES_2, 20, 100, IDR_WAVE2, FALSE);

    FRAME HYPSOKINESIS_1 = { IDB_HYPSOKINESIS_1 ,0, 13 };
    FRAME HYPSOKINESIS_2 = { IDB_HYPSOKINESIS_2 ,0, 13 };
    FRAME HYPSOKINESIS_3 = { IDB_HYPSOKINESIS_3 ,0, 13 };
    FRAME HYPSOKINESIS_4 = { IDB_HYPSOKINESIS_4 ,0, 13 };
    FRAME HYPSOKINESIS_5 = { IDB_HYPSOKINESIS_5 ,0, 13 };
    FRAME HYPSOKINESIS_6 = { IDB_HYPSOKINESIS_6 ,0, 13 };
    FRAME HYPSOKINESIS_7 = { IDB_HYPSOKINESIS_7 ,0, 13 };
    FRAME HYPSOKINESIS_FRAMES_1[] = { HYPSOKINESIS_1 ,HYPSOKINESIS_2, HYPSOKINESIS_3, HYPSOKINESIS_4, HYPSOKINESIS_5 };
    HYPSOKINESIS_ACTION_1 = CreateAnimationAction(HYPSOKINESIS_FRAMES_1, 5, 35, NULL, FALSE);
    FRAME HYPSOKINESIS_FRAMES_2[] = { HYPSOKINESIS_5 };
    HYPSOKINESIS_ACTION_2 = CreateAnimationAction(HYPSOKINESIS_FRAMES_2, 1, 50, IDR_WAVE3, FALSE);
    FRAME HYPSOKINESIS_FRAMES_3[] = { HYPSOKINESIS_5, HYPSOKINESIS_6, HYPSOKINESIS_7, USUAL };
    HYPSOKINESIS_ACTION_3 = CreateAnimationAction(HYPSOKINESIS_FRAMES_3, 4, 80, NULL, FALSE);

    FRAME CLICK_FRAMES[] = { USUAL };
    CLICK_ACTION = CreateAnimationAction(INIT_FRAMES, 1, 50, IDR_WAVE4, FALSE);
    FRAME OTHER_FRAMES[] = { USUAL };
    OTHER_ACTION = CreateAnimationAction(OTHER_FRAMES, 1, 50, IDR_WAVE5, FALSE);

    OPTIONS options;
    options.WINPOS = 30;
    options.selection = SELECTION::StartMenu;
    options.SOUND = TRUE;
    options.ANIMATION = TRUE;

    LPCWSTR appName = L"Kaolla";

    LoadOptions(hInstance, appName, &options);

    sprite = new Sprite(hInstance, appName, 64, 96, &options);
    sprite->SetClickHook(MouseLeftButtonHook);
    sprite->SetFrame(USUAL);
    sprite->Show();

    stateMachine = new StateMachine<StateEvent>;
    // 初始状态
    State<StateEvent>* initState = new State<StateEvent>;
    initState->setExec([]() { sprite->PlayAnimation(INIT_ACTION); });
    // 终止状态
    State<StateEvent>* exitState = new State<StateEvent>;
    exitState->setEnter([]() { KillTimer(sprite->GetHandle(), IDT_TRIGGER_ANIMATION); });
    // 随机设置触发时间
    State<StateEvent>* randomTimerState = new State<StateEvent>;
    randomTimerState->setExec([]() { SetTimer(sprite->GetHandle(), IDT_TRIGGER_ANIMATION, RandomRange(5000, 15000), ActionTimer); });
    // 随机触发动画
    State<StateEvent>* randomTriggerState = new State<StateEvent>;
    randomTriggerState->setEnter([]() { KillTimer(sprite->GetHandle(), IDT_TRIGGER_ANIMATION); });
    randomTriggerState->setExec([]() {
        if (GetProb() <= 0.75f) {
            sprite->PlayAnimation(BLINK_ACTION);
        }
        else {
            float prob = GetProb();
            if (prob <= 0.25f) {
                sprite->PlayAnimation(LAUGH_ACTION_A);
            }
            else if (prob <= 0.5f) {
                sprite->PlayAnimation(LAUGH_ACTION_B);
            }
            else if (prob <= 0.75f) {
                stateMachine->doAction(StateEvent::PLAY_HYPSOKINESIS);
                return;
            }
            else {
                sprite->PlayAnimation(OTHER_ACTION);
            }
        }
        stateMachine->doAction(StateEvent::CONTINUE);
    });
    // 点击动画
    State<StateEvent>* clickState = new State<StateEvent>;
    clickState->setEnter([]() { KillTimer(sprite->GetHandle(), IDT_TRIGGER_ANIMATION); });
    clickState->setExec([]() {
        sprite->PlayAnimation(CLICK_ACTION);
        stateMachine->doAction(StateEvent::CONTINUE);
    });
    // 翻身动画
    State<StateEvent>* hypsokinesis1State = new State<StateEvent>;
    hypsokinesis1State->setEnter([]() { KillTimer(sprite->GetHandle(), IDT_TRIGGER_ANIMATION); });
    hypsokinesis1State->setExec([]() {
        sprite->PlayAnimation(HYPSOKINESIS_ACTION_1);
        SetTimer(sprite->GetHandle(), IDT_TRIGGER_ANIMATION, RandomRange(5000, 15000), ActionTimer);
    });
    State<StateEvent>* hypsokinesis2State = new State<StateEvent>;
    hypsokinesis2State->setEnter([]() { KillTimer(sprite->GetHandle(), IDT_TRIGGER_ANIMATION); });
    hypsokinesis2State->setExec([]() {
        sprite->PlayAnimation(HYPSOKINESIS_ACTION_2);
        SetTimer(sprite->GetHandle(), IDT_TRIGGER_ANIMATION, 3500, ActionTimer);
    });
    State<StateEvent>* hypsokinesis3State = new State<StateEvent>;
    hypsokinesis3State->setEnter([]() { KillTimer(sprite->GetHandle(), IDT_TRIGGER_ANIMATION); });
    hypsokinesis3State->setExec([]() {
        sprite->PlayAnimation(HYPSOKINESIS_ACTION_3);
        stateMachine->doAction(StateEvent::CONTINUE);
    });

    initState->addTransition(StateEvent::CONTINUE, randomTimerState);
    initState->addTransition(StateEvent::EXIT, exitState);
    randomTimerState->addTransition(StateEvent::CONTINUE, randomTriggerState);
    randomTimerState->addTransition(StateEvent::EXIT, exitState);
    randomTimerState->addTransition(StateEvent::CLICK, clickState);
    randomTriggerState->addTransition(StateEvent::CONTINUE, randomTimerState);
    randomTriggerState->addTransition(StateEvent::EXIT, exitState);
    randomTriggerState->addTransition(StateEvent::PLAY_HYPSOKINESIS, hypsokinesis1State);
    clickState->addTransition(StateEvent::CONTINUE, randomTimerState);
    clickState->addTransition(StateEvent::EXIT, exitState);
    hypsokinesis1State->addTransition(StateEvent::CONTINUE, hypsokinesis2State);
    hypsokinesis1State->addTransition(StateEvent::EXIT, exitState);
    hypsokinesis1State->addTransition(StateEvent::CLICK, hypsokinesis3State);
    hypsokinesis2State->addTransition(StateEvent::CONTINUE, hypsokinesis3State);
    hypsokinesis2State->addTransition(StateEvent::EXIT, exitState);
    hypsokinesis3State->addTransition(StateEvent::CONTINUE, randomTimerState);
    hypsokinesis3State->addTransition(StateEvent::EXIT, exitState);

    stateMachine->initState(initState);
    stateMachine->addState(exitState);
    stateMachine->addState(randomTimerState);
    stateMachine->addState(randomTriggerState);
    stateMachine->addState(clickState);
    stateMachine->addState(hypsokinesis1State);
    stateMachine->addState(hypsokinesis2State);
    stateMachine->addState(hypsokinesis3State);
    stateMachine->start();
    stateMachine->doAction(StateEvent::CONTINUE);

    int ret = sprite->EventLoop();
    const OPTIONS* lastOptions = sprite->GetOptions();
    SaveOptions(hInstance, appName, lastOptions);

    stateMachine->doAction(StateEvent::EXIT);
    delete stateMachine;
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
