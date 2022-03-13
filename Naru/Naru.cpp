#include "../Sprite/ISprite.h"
#include "resource.h"
#include "../Kaolla/random.h"

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
const ACTION* CLOTHES_A_ACTION_BLINK = NULL;
const ACTION* CLOTHES_A_ACTION_1 = NULL;
const ACTION* CLOTHES_A_ACTION_2 = NULL;
const ACTION* CLOTHES_A_ACTION_3 = NULL;
const ACTION* CLOTHES_A_ACTION_4 = NULL;
const ACTION* CLOTHES_A_ACTION_5 = NULL;

const ACTION* CLOTHES_B_ACTION_BLINK = NULL;
const ACTION* CLOTHES_B_ACTION_1 = NULL;
const ACTION* CLOTHES_B_ACTION_2 = NULL;
const ACTION* CLOTHES_B_ACTION_3 = NULL;
const ACTION* CLOTHES_B_ACTION_4 = NULL;
const ACTION* CLOTHES_B_ACTION_5 = NULL;

const ACTION* CLOTHES_C_ACTION_BLINK = NULL;
const ACTION* CLOTHES_C_ACTION_1 = NULL;
const ACTION* CLOTHES_C_ACTION_2 = NULL;
const ACTION* CLOTHES_C_ACTION_3 = NULL;
const ACTION* CLOTHES_C_ACTION_4 = NULL;
const ACTION* CLOTHES_C_ACTION_5 = NULL;

const ACTION* CLOTHES_D_ACTION_BLINK = NULL;
const ACTION* CLOTHES_D_ACTION_1 = NULL;
const ACTION* CLOTHES_D_ACTION_2 = NULL;
const ACTION* CLOTHES_D_ACTION_3 = NULL;
const ACTION* CLOTHES_D_ACTION_4 = NULL;
const ACTION* CLOTHES_D_ACTION_5 = NULL;

const ACTION* CLOTHES_E_ACTION_BLINK = NULL;
const ACTION* CLOTHES_E_ACTION_1 = NULL;
const ACTION* CLOTHES_E_ACTION_2 = NULL;
const ACTION* CLOTHES_E_ACTION_3 = NULL;
const ACTION* CLOTHES_E_ACTION_4 = NULL;
const ACTION* CLOTHES_E_ACTION_5 = NULL;

const ACTION* CLOTHES_F_ACTION_BLINK = NULL;
const ACTION* CLOTHES_F_ACTION_1 = NULL;
const ACTION* CLOTHES_F_ACTION_2 = NULL;
const ACTION* CLOTHES_F_ACTION_3 = NULL;
const ACTION* CLOTHES_F_ACTION_4 = NULL;
const ACTION* CLOTHES_F_ACTION_5 = NULL;

const ACTION* CLOTHES_G_ACTION_BLINK = NULL;
const ACTION* CLOTHES_G_ACTION_1 = NULL;
const ACTION* CLOTHES_G_ACTION_2 = NULL;
const ACTION* CLOTHES_G_ACTION_3 = NULL;
const ACTION* CLOTHES_G_ACTION_4 = NULL;
const ACTION* CLOTHES_G_ACTION_5 = NULL;

const ACTION* CLOTHES_H_ACTION_BLINK = NULL;
const ACTION* CLOTHES_H_ACTION_1 = NULL;
const ACTION* CLOTHES_H_ACTION_2 = NULL;
const ACTION* CLOTHES_H_ACTION_3 = NULL;
const ACTION* CLOTHES_H_ACTION_4 = NULL;
const ACTION* CLOTHES_H_ACTION_5 = NULL;

const ACTION* CLOTHES_I_ACTION_BLINK = NULL;
const ACTION* CLOTHES_I_ACTION_1 = NULL;
const ACTION* CLOTHES_I_ACTION_2 = NULL;
const ACTION* CLOTHES_I_ACTION_3 = NULL;
const ACTION* CLOTHES_I_ACTION_4 = NULL;
const ACTION* CLOTHES_I_ACTION_5 = NULL;

const ACTION* CLOTHES_J_ACTION_BLINK = NULL;
const ACTION* CLOTHES_J_ACTION_1 = NULL;
const ACTION* CLOTHES_J_ACTION_2 = NULL;
const ACTION* CLOTHES_J_ACTION_3 = NULL;
const ACTION* CLOTHES_J_ACTION_4 = NULL;
const ACTION* CLOTHES_J_ACTION_5 = NULL;

const ACTION* CLOTHES_K_ACTION_BLINK = NULL;
const ACTION* CLOTHES_K_ACTION_1 = NULL;
const ACTION* CLOTHES_K_ACTION_2 = NULL;
const ACTION* CLOTHES_K_ACTION_3 = NULL;
const ACTION* CLOTHES_K_ACTION_4 = NULL;
const ACTION* CLOTHES_K_ACTION_5 = NULL;

const ACTION* CLOTHES_L_ACTION_BLINK = NULL;
const ACTION* CLOTHES_L_ACTION_1 = NULL;
const ACTION* CLOTHES_L_ACTION_2 = NULL;
const ACTION* CLOTHES_L_ACTION_3 = NULL;
const ACTION* CLOTHES_L_ACTION_4 = NULL;
const ACTION* CLOTHES_L_ACTION_5 = NULL;

VOID CALLBACK ActionTimer(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
UINT CLOTHING_NUMBER = 1;
void ExecAction(UINT actionNum) {
    KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
    switch (CLOTHING_NUMBER){
    case 1:
        switch (actionNum)
        {
        case 0:
            pSprite->PlayAnimation(CLOTHES_A_ACTION_BLINK);
            break;
        case 1:
            pSprite->PlayAnimation(CLOTHES_A_ACTION_1);
            break;
        case 2:
            pSprite->PlayAnimation(CLOTHES_A_ACTION_2);
            break;
        case 3:
            pSprite->PlayAnimation(CLOTHES_A_ACTION_3);
            break;
        case 4:
            pSprite->PlayAnimation(CLOTHES_A_ACTION_4);
            break;
        case 5:
            pSprite->PlayAnimation(CLOTHES_A_ACTION_5);
            break;
        }
        break;
    case 2:
        switch (actionNum)
        {
        case 0:
            pSprite->PlayAnimation(CLOTHES_B_ACTION_BLINK);
            break;
        case 1:
            pSprite->PlayAnimation(CLOTHES_B_ACTION_1);
            break;
        case 2:
            pSprite->PlayAnimation(CLOTHES_B_ACTION_2);
            break;
        case 3:
            pSprite->PlayAnimation(CLOTHES_B_ACTION_3);
            break;
        case 4:
            pSprite->PlayAnimation(CLOTHES_B_ACTION_4);
            break;
        case 5:
            pSprite->PlayAnimation(CLOTHES_B_ACTION_5);
            break;
        }
        break;
    case 3:
        switch (actionNum)
        {
        case 0:
            pSprite->PlayAnimation(CLOTHES_C_ACTION_BLINK);
            break;
        case 1:
            pSprite->PlayAnimation(CLOTHES_C_ACTION_1);
            break;
        case 2:
            pSprite->PlayAnimation(CLOTHES_C_ACTION_2);
            break;
        case 3:
            pSprite->PlayAnimation(CLOTHES_C_ACTION_3);
            break;
        case 4:
            pSprite->PlayAnimation(CLOTHES_C_ACTION_4);
            break;
        case 5:
            pSprite->PlayAnimation(CLOTHES_C_ACTION_5);
            break;
        }
        break;
    case 4:
        switch (actionNum)
        {
        case 0:
            pSprite->PlayAnimation(CLOTHES_D_ACTION_BLINK);
            break;
        case 1:
            pSprite->PlayAnimation(CLOTHES_D_ACTION_1);
            break;
        case 2:
            pSprite->PlayAnimation(CLOTHES_D_ACTION_2);
            break;
        case 3:
            pSprite->PlayAnimation(CLOTHES_D_ACTION_3);
            break;
        case 4:
            pSprite->PlayAnimation(CLOTHES_D_ACTION_4);
            break;
        case 5:
            pSprite->PlayAnimation(CLOTHES_D_ACTION_5);
            break;
        }
        break;
    case 5:
        switch (actionNum)
        {
        case 0:
            pSprite->PlayAnimation(CLOTHES_E_ACTION_BLINK);
            break;
        case 1:
            pSprite->PlayAnimation(CLOTHES_E_ACTION_1);
            break;
        case 2:
            pSprite->PlayAnimation(CLOTHES_E_ACTION_2);
            break;
        case 3:
            pSprite->PlayAnimation(CLOTHES_E_ACTION_3);
            break;
        case 4:
            pSprite->PlayAnimation(CLOTHES_E_ACTION_4);
            break;
        case 5:
            pSprite->PlayAnimation(CLOTHES_E_ACTION_5);
            break;
        }
        break;
    case 6:
        switch (actionNum)
        {
        case 0:
            pSprite->PlayAnimation(CLOTHES_F_ACTION_BLINK);
            break;
        case 1:
            pSprite->PlayAnimation(CLOTHES_F_ACTION_1);
            break;
        case 2:
            pSprite->PlayAnimation(CLOTHES_F_ACTION_2);
            break;
        case 3:
            pSprite->PlayAnimation(CLOTHES_F_ACTION_3);
            break;
        case 4:
            pSprite->PlayAnimation(CLOTHES_F_ACTION_4);
            break;
        case 5:
            pSprite->PlayAnimation(CLOTHES_F_ACTION_5);
            break;
        }
        break;
    case 7:
        switch (actionNum)
        {
        case 0:
            pSprite->PlayAnimation(CLOTHES_G_ACTION_BLINK);
            break;
        case 1:
            pSprite->PlayAnimation(CLOTHES_G_ACTION_1);
            break;
        case 2:
            pSprite->PlayAnimation(CLOTHES_G_ACTION_2);
            break;
        case 3:
            pSprite->PlayAnimation(CLOTHES_G_ACTION_3);
            break;
        case 4:
            pSprite->PlayAnimation(CLOTHES_G_ACTION_4);
            break;
        case 5:
            pSprite->PlayAnimation(CLOTHES_G_ACTION_5);
            break;
        }
        break;
    case 8:
        switch (actionNum)
        {
        case 0:
            pSprite->PlayAnimation(CLOTHES_H_ACTION_BLINK);
            break;
        case 1:
            pSprite->PlayAnimation(CLOTHES_H_ACTION_1);
            break;
        case 2:
            pSprite->PlayAnimation(CLOTHES_H_ACTION_2);
            break;
        case 3:
            pSprite->PlayAnimation(CLOTHES_H_ACTION_3);
            break;
        case 4:
            pSprite->PlayAnimation(CLOTHES_H_ACTION_4);
            break;
        case 5:
            pSprite->PlayAnimation(CLOTHES_H_ACTION_5);
            break;
        }
        break;
    case 9:
        switch (actionNum)
        {
        case 0:
            pSprite->PlayAnimation(CLOTHES_I_ACTION_BLINK);
            break;
        case 1:
            pSprite->PlayAnimation(CLOTHES_I_ACTION_1);
            break;
        case 2:
            pSprite->PlayAnimation(CLOTHES_I_ACTION_2);
            break;
        case 3:
            pSprite->PlayAnimation(CLOTHES_I_ACTION_3);
            break;
        case 4:
            pSprite->PlayAnimation(CLOTHES_I_ACTION_4);
            break;
        case 5:
            pSprite->PlayAnimation(CLOTHES_I_ACTION_5);
            break;
        }
        break;
    case 10:
        switch (actionNum)
        {
        case 0:
            pSprite->PlayAnimation(CLOTHES_J_ACTION_BLINK);
            break;
        case 1:
            pSprite->PlayAnimation(CLOTHES_J_ACTION_1);
            break;
        case 2:
            pSprite->PlayAnimation(CLOTHES_J_ACTION_2);
            break;
        case 3:
            pSprite->PlayAnimation(CLOTHES_J_ACTION_3);
            break;
        case 4:
            pSprite->PlayAnimation(CLOTHES_J_ACTION_4);
            break;
        case 5:
            pSprite->PlayAnimation(CLOTHES_J_ACTION_5);
            break;
        }
        break;
    case 11:
        switch (actionNum)
        {
        case 0:
            pSprite->PlayAnimation(CLOTHES_K_ACTION_BLINK);
            break;
        case 1:
            pSprite->PlayAnimation(CLOTHES_K_ACTION_1);
            break;
        case 2:
            pSprite->PlayAnimation(CLOTHES_K_ACTION_2);
            break;
        case 3:
            pSprite->PlayAnimation(CLOTHES_K_ACTION_3);
            break;
        case 4:
            pSprite->PlayAnimation(CLOTHES_K_ACTION_4);
            break;
        case 5:
            pSprite->PlayAnimation(CLOTHES_K_ACTION_5);
            break;
        }
        break;
    case 12:
        switch (actionNum)
        {
        case 0:
            pSprite->PlayAnimation(CLOTHES_L_ACTION_BLINK);
            break;
        case 1:
            pSprite->PlayAnimation(CLOTHES_L_ACTION_1);
            break;
        case 2:
            pSprite->PlayAnimation(CLOTHES_L_ACTION_2);
            break;
        case 3:
            pSprite->PlayAnimation(CLOTHES_L_ACTION_3);
            break;
        case 4:
            pSprite->PlayAnimation(CLOTHES_L_ACTION_4);
            break;
        case 5:
            pSprite->PlayAnimation(CLOTHES_L_ACTION_5);
            break;
        }
        break;
    }
    SetTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION, RandomRange(5000, 10000), ActionTimer);
}

VOID CALLBACK ActionTimer(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    if (idEvent == IDT_TRIGGER_ANIMATION) {
        if (GetProb() <= 0.75f) {
            ExecAction(0);
        }
        else {
            ExecAction(RandomRange(1, 5));
        }
    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    FRAME CLOTHES_A_1 = { IDB_CLOTHES_A_1 , 0, 21 };
    FRAME CLOTHES_A_2 = { IDB_CLOTHES_A_2 , 0, 21 };
    FRAME CLOTHES_A_3 = { IDB_CLOTHES_A_3 , 0, 21 };
    FRAME CLOTHES_A_BLINK_FRAMES[] = { CLOTHES_A_1, CLOTHES_A_2, CLOTHES_A_3 };
    CLOTHES_A_ACTION_BLINK = CreateAnimationAction(CLOTHES_A_BLINK_FRAMES, 3, 90, NULL, FALSE);
    CLOTHES_A_ACTION_1 = CreateAnimationAction(&CLOTHES_A_3, 1, 50, IDR_WAVE1, FALSE);
    CLOTHES_A_ACTION_2 = CreateAnimationAction(&CLOTHES_A_3, 1, 50, IDR_WAVE2, FALSE);
    CLOTHES_A_ACTION_3 = CreateAnimationAction(&CLOTHES_A_3, 1, 50, IDR_WAVE3, FALSE);
    CLOTHES_A_ACTION_4 = CreateAnimationAction(&CLOTHES_A_3, 1, 50, IDR_WAVE4, FALSE);
    CLOTHES_A_ACTION_5 = CreateAnimationAction(&CLOTHES_A_3, 1, 50, IDR_WAVE5, FALSE);

    FRAME CLOTHES_B_1 = { IDB_CLOTHES_B_1 , 0, 21 };
    FRAME CLOTHES_B_2 = { IDB_CLOTHES_B_2 , 0, 21 };
    FRAME CLOTHES_B_3 = { IDB_CLOTHES_B_3 , 0, 21 };
    FRAME CLOTHES_B_BLINK_FRAMES[] = { CLOTHES_B_1, CLOTHES_B_2, CLOTHES_B_3 };
    CLOTHES_B_ACTION_BLINK = CreateAnimationAction(CLOTHES_B_BLINK_FRAMES, 3, 90, NULL, FALSE);
    CLOTHES_B_ACTION_1 = CreateAnimationAction(&CLOTHES_B_3, 1, 50, IDR_WAVE1, FALSE);
    CLOTHES_B_ACTION_2 = CreateAnimationAction(&CLOTHES_B_3, 1, 50, IDR_WAVE2, FALSE);
    CLOTHES_B_ACTION_3 = CreateAnimationAction(&CLOTHES_B_3, 1, 50, IDR_WAVE3, FALSE);
    CLOTHES_B_ACTION_4 = CreateAnimationAction(&CLOTHES_B_3, 1, 50, IDR_WAVE4, FALSE);
    CLOTHES_B_ACTION_5 = CreateAnimationAction(&CLOTHES_B_3, 1, 50, IDR_WAVE5, FALSE);

    FRAME CLOTHES_C_1 = { IDB_CLOTHES_C_1 , 0, 21 };
    FRAME CLOTHES_C_2 = { IDB_CLOTHES_C_2 , 0, 21 };
    FRAME CLOTHES_C_3 = { IDB_CLOTHES_C_3 , 0, 21 };
    FRAME CLOTHES_C_BLINK_FRAMES[] = { CLOTHES_C_1, CLOTHES_C_2, CLOTHES_C_3 };
    CLOTHES_C_ACTION_BLINK = CreateAnimationAction(CLOTHES_C_BLINK_FRAMES, 3, 90, NULL, FALSE);
    CLOTHES_C_ACTION_1 = CreateAnimationAction(&CLOTHES_C_3, 1, 50, IDR_WAVE1, FALSE);
    CLOTHES_C_ACTION_2 = CreateAnimationAction(&CLOTHES_C_3, 1, 50, IDR_WAVE2, FALSE);
    CLOTHES_C_ACTION_3 = CreateAnimationAction(&CLOTHES_C_3, 1, 50, IDR_WAVE3, FALSE);
    CLOTHES_C_ACTION_4 = CreateAnimationAction(&CLOTHES_C_3, 1, 50, IDR_WAVE4, FALSE);
    CLOTHES_C_ACTION_5 = CreateAnimationAction(&CLOTHES_C_3, 1, 50, IDR_WAVE5, FALSE);

    FRAME CLOTHES_D_1 = { IDB_CLOTHES_D_1 , 0, 21 };
    FRAME CLOTHES_D_2 = { IDB_CLOTHES_D_2 , 0, 21 };
    FRAME CLOTHES_D_3 = { IDB_CLOTHES_D_3 , 0, 21 };
    FRAME CLOTHES_D_BLINK_FRAMES[] = { CLOTHES_D_1, CLOTHES_D_2, CLOTHES_D_3 };
    CLOTHES_D_ACTION_BLINK = CreateAnimationAction(CLOTHES_D_BLINK_FRAMES, 3, 90, NULL, FALSE);
    CLOTHES_D_ACTION_1 = CreateAnimationAction(&CLOTHES_D_3, 1, 50, IDR_WAVE1, FALSE);
    CLOTHES_D_ACTION_2 = CreateAnimationAction(&CLOTHES_D_3, 1, 50, IDR_WAVE2, FALSE);
    CLOTHES_D_ACTION_3 = CreateAnimationAction(&CLOTHES_D_3, 1, 50, IDR_WAVE3, FALSE);
    CLOTHES_D_ACTION_4 = CreateAnimationAction(&CLOTHES_D_3, 1, 50, IDR_WAVE4, FALSE);
    CLOTHES_D_ACTION_5 = CreateAnimationAction(&CLOTHES_D_3, 1, 50, IDR_WAVE5, FALSE);

    FRAME CLOTHES_E_1 = { IDB_CLOTHES_E_1 , 0, 21 };
    FRAME CLOTHES_E_2 = { IDB_CLOTHES_E_2 , 0, 21 };
    FRAME CLOTHES_E_3 = { IDB_CLOTHES_E_3 , 0, 21 };
    FRAME CLOTHES_E_BLINK_FRAMES[] = { CLOTHES_E_1, CLOTHES_E_2, CLOTHES_E_3 };
    CLOTHES_E_ACTION_BLINK = CreateAnimationAction(CLOTHES_E_BLINK_FRAMES, 3, 90, NULL, FALSE);
    CLOTHES_E_ACTION_1 = CreateAnimationAction(&CLOTHES_E_3, 1, 50, IDR_WAVE1, FALSE);
    CLOTHES_E_ACTION_2 = CreateAnimationAction(&CLOTHES_E_3, 1, 50, IDR_WAVE2, FALSE);
    CLOTHES_E_ACTION_3 = CreateAnimationAction(&CLOTHES_E_3, 1, 50, IDR_WAVE3, FALSE);
    CLOTHES_E_ACTION_4 = CreateAnimationAction(&CLOTHES_E_3, 1, 50, IDR_WAVE4, FALSE);
    CLOTHES_E_ACTION_5 = CreateAnimationAction(&CLOTHES_E_3, 1, 50, IDR_WAVE5, FALSE);

    FRAME CLOTHES_F_1 = { IDB_CLOTHES_F_1 , 0, 21 };
    FRAME CLOTHES_F_2 = { IDB_CLOTHES_F_2 , 0, 21 };
    FRAME CLOTHES_F_3 = { IDB_CLOTHES_F_3 , 0, 21 };
    FRAME CLOTHES_F_BLINK_FRAMES[] = { CLOTHES_F_1, CLOTHES_F_2, CLOTHES_F_3 };
    CLOTHES_F_ACTION_BLINK = CreateAnimationAction(CLOTHES_F_BLINK_FRAMES, 3, 90, NULL, FALSE);
    CLOTHES_F_ACTION_1 = CreateAnimationAction(&CLOTHES_F_3, 1, 50, IDR_WAVE1, FALSE);
    CLOTHES_F_ACTION_2 = CreateAnimationAction(&CLOTHES_F_3, 1, 50, IDR_WAVE2, FALSE);
    CLOTHES_F_ACTION_3 = CreateAnimationAction(&CLOTHES_F_3, 1, 50, IDR_WAVE3, FALSE);
    CLOTHES_F_ACTION_4 = CreateAnimationAction(&CLOTHES_F_3, 1, 50, IDR_WAVE4, FALSE);
    CLOTHES_F_ACTION_5 = CreateAnimationAction(&CLOTHES_F_3, 1, 50, IDR_WAVE5, FALSE);

    FRAME CLOTHES_G_1 = { IDB_CLOTHES_G_1 , 0, 21 };
    FRAME CLOTHES_G_2 = { IDB_CLOTHES_G_2 , 0, 21 };
    FRAME CLOTHES_G_3 = { IDB_CLOTHES_G_3 , 0, 21 };
    FRAME CLOTHES_G_BLINK_FRAMES[] = { CLOTHES_G_1, CLOTHES_G_2, CLOTHES_G_3 };
    CLOTHES_G_ACTION_BLINK = CreateAnimationAction(CLOTHES_G_BLINK_FRAMES, 3, 90, NULL, FALSE);
    CLOTHES_G_ACTION_1 = CreateAnimationAction(&CLOTHES_G_3, 1, 50, IDR_WAVE1, FALSE);
    CLOTHES_G_ACTION_2 = CreateAnimationAction(&CLOTHES_G_3, 1, 50, IDR_WAVE2, FALSE);
    CLOTHES_G_ACTION_3 = CreateAnimationAction(&CLOTHES_G_3, 1, 50, IDR_WAVE3, FALSE);
    CLOTHES_G_ACTION_4 = CreateAnimationAction(&CLOTHES_G_3, 1, 50, IDR_WAVE4, FALSE);
    CLOTHES_G_ACTION_5 = CreateAnimationAction(&CLOTHES_G_3, 1, 50, IDR_WAVE5, FALSE);

    FRAME CLOTHES_H_1 = { IDB_CLOTHES_H_1 , 0, 21 };
    FRAME CLOTHES_H_2 = { IDB_CLOTHES_H_2 , 0, 21 };
    FRAME CLOTHES_H_3 = { IDB_CLOTHES_H_3 , 0, 21 };
    FRAME CLOTHES_H_BLINK_FRAMES[] = { CLOTHES_H_1, CLOTHES_H_2, CLOTHES_H_3 };
    CLOTHES_H_ACTION_BLINK = CreateAnimationAction(CLOTHES_H_BLINK_FRAMES, 3, 90, NULL, FALSE);
    CLOTHES_H_ACTION_1 = CreateAnimationAction(&CLOTHES_H_3, 1, 50, IDR_WAVE1, FALSE);
    CLOTHES_H_ACTION_2 = CreateAnimationAction(&CLOTHES_H_3, 1, 50, IDR_WAVE2, FALSE);
    CLOTHES_H_ACTION_3 = CreateAnimationAction(&CLOTHES_H_3, 1, 50, IDR_WAVE3, FALSE);
    CLOTHES_H_ACTION_4 = CreateAnimationAction(&CLOTHES_H_3, 1, 50, IDR_WAVE4, FALSE);
    CLOTHES_H_ACTION_5 = CreateAnimationAction(&CLOTHES_H_3, 1, 50, IDR_WAVE5, FALSE);

    FRAME CLOTHES_I_1 = { IDB_CLOTHES_I_1 , 0, 21 };
    FRAME CLOTHES_I_2 = { IDB_CLOTHES_I_2 , 0, 21 };
    FRAME CLOTHES_I_3 = { IDB_CLOTHES_I_3 , 0, 21 };
    FRAME CLOTHES_I_BLINK_FRAMES[] = { CLOTHES_I_1, CLOTHES_I_2, CLOTHES_I_3 };
    CLOTHES_I_ACTION_BLINK = CreateAnimationAction(CLOTHES_I_BLINK_FRAMES, 3, 90, NULL, FALSE);
    CLOTHES_I_ACTION_1 = CreateAnimationAction(&CLOTHES_I_3, 1, 50, IDR_WAVE1, FALSE);
    CLOTHES_I_ACTION_2 = CreateAnimationAction(&CLOTHES_I_3, 1, 50, IDR_WAVE2, FALSE);
    CLOTHES_I_ACTION_3 = CreateAnimationAction(&CLOTHES_I_3, 1, 50, IDR_WAVE3, FALSE);
    CLOTHES_I_ACTION_4 = CreateAnimationAction(&CLOTHES_I_3, 1, 50, IDR_WAVE4, FALSE);
    CLOTHES_I_ACTION_5 = CreateAnimationAction(&CLOTHES_I_3, 1, 50, IDR_WAVE5, FALSE);

    FRAME CLOTHES_J_1 = { IDB_CLOTHES_J_1 , 0, 21 };
    FRAME CLOTHES_J_2 = { IDB_CLOTHES_J_2 , 0, 21 };
    FRAME CLOTHES_J_3 = { IDB_CLOTHES_J_3 , 0, 21 };
    FRAME CLOTHES_J_BLINK_FRAMES[] = { CLOTHES_J_1, CLOTHES_J_2, CLOTHES_J_3 };
    CLOTHES_J_ACTION_BLINK = CreateAnimationAction(CLOTHES_J_BLINK_FRAMES, 3, 90, NULL, FALSE);
    CLOTHES_J_ACTION_1 = CreateAnimationAction(&CLOTHES_J_3, 1, 50, IDR_WAVE1, FALSE);
    CLOTHES_J_ACTION_2 = CreateAnimationAction(&CLOTHES_J_3, 1, 50, IDR_WAVE2, FALSE);
    CLOTHES_J_ACTION_3 = CreateAnimationAction(&CLOTHES_J_3, 1, 50, IDR_WAVE3, FALSE);
    CLOTHES_J_ACTION_4 = CreateAnimationAction(&CLOTHES_J_3, 1, 50, IDR_WAVE4, FALSE);
    CLOTHES_J_ACTION_5 = CreateAnimationAction(&CLOTHES_J_3, 1, 50, IDR_WAVE5, FALSE);

    FRAME CLOTHES_K_1 = { IDB_CLOTHES_K_1 , 0, 21 };
    FRAME CLOTHES_K_2 = { IDB_CLOTHES_K_2 , 0, 21 };
    FRAME CLOTHES_K_3 = { IDB_CLOTHES_K_3 , 0, 21 };
    FRAME CLOTHES_K_BLINK_FRAMES[] = { CLOTHES_K_1, CLOTHES_K_2, CLOTHES_K_3 };
    CLOTHES_K_ACTION_BLINK = CreateAnimationAction(CLOTHES_K_BLINK_FRAMES, 3, 90, NULL, FALSE);
    CLOTHES_K_ACTION_1 = CreateAnimationAction(&CLOTHES_K_3, 1, 50, IDR_WAVE1, FALSE);
    CLOTHES_K_ACTION_2 = CreateAnimationAction(&CLOTHES_K_3, 1, 50, IDR_WAVE2, FALSE);
    CLOTHES_K_ACTION_3 = CreateAnimationAction(&CLOTHES_K_3, 1, 50, IDR_WAVE3, FALSE);
    CLOTHES_K_ACTION_4 = CreateAnimationAction(&CLOTHES_K_3, 1, 50, IDR_WAVE4, FALSE);
    CLOTHES_K_ACTION_5 = CreateAnimationAction(&CLOTHES_K_3, 1, 50, IDR_WAVE5, FALSE);

    FRAME CLOTHES_L_1 = { IDB_CLOTHES_L_1 , 0, 21 };
    FRAME CLOTHES_L_2 = { IDB_CLOTHES_L_2 , 0, 21 };
    FRAME CLOTHES_L_3 = { IDB_CLOTHES_L_3 , 0, 21 };
    FRAME CLOTHES_L_BLINK_FRAMES[] = { CLOTHES_L_1, CLOTHES_L_2, CLOTHES_L_3 };
    CLOTHES_L_ACTION_BLINK = CreateAnimationAction(CLOTHES_L_BLINK_FRAMES, 3, 90, NULL, FALSE);
    CLOTHES_L_ACTION_1 = CreateAnimationAction(&CLOTHES_L_3, 1, 50, IDR_WAVE1, FALSE);
    CLOTHES_L_ACTION_2 = CreateAnimationAction(&CLOTHES_L_3, 1, 50, IDR_WAVE2, FALSE);
    CLOTHES_L_ACTION_3 = CreateAnimationAction(&CLOTHES_L_3, 1, 50, IDR_WAVE3, FALSE);
    CLOTHES_L_ACTION_4 = CreateAnimationAction(&CLOTHES_L_3, 1, 50, IDR_WAVE4, FALSE);
    CLOTHES_L_ACTION_5 = CreateAnimationAction(&CLOTHES_L_3, 1, 50, IDR_WAVE5, FALSE);

    OPTIONS options = { 90, TRUE, TRUE, SELECTION::StartMenu };
    pSprite = CreateSprite(hInstance, L"Naru", 80, 120, &options);
    HMENU hMenu = pSprite->AppendPopupMenu(L"服装选项");
    pSprite->AppendChildMenu(hMenu, 0xF100, L"自动选择");
    pSprite->AppendChildMenu(hMenu, NULL, NULL);
    pSprite->AppendChildMenu(hMenu, 0xF101, L"服装1");
    pSprite->AppendChildMenu(hMenu, 0xF102, L"服装2");
    pSprite->AppendChildMenu(hMenu, 0xF103, L"服装3");
    pSprite->AppendChildMenu(hMenu, 0xF104, L"服装4");
    pSprite->AppendChildMenu(hMenu, 0xF105, L"服装5");
    pSprite->AppendChildMenu(hMenu, 0xF106, L"服装6");
    pSprite->AppendChildMenu(hMenu, 0xF107, L"服装7");
    pSprite->AppendChildMenu(hMenu, 0xF108, L"服装8");
    pSprite->AppendChildMenu(hMenu, 0xF109, L"服装9");
    pSprite->AppendChildMenu(hMenu, 0xF10A, L"服装10");
    pSprite->AppendChildMenu(hMenu, 0xF10B, L"服装11");
    pSprite->AppendChildMenu(hMenu, 0xF10C, L"服装12");
    pSprite->SetMenuCommandHook([](HMENU hMenu, UINT id) {
        UINT clothingNumber = id & 0xff;
        for (int i = 0xF100; i <= 0xF112; i++) {
            CheckMenuItem(hMenu, i, MF_BYCOMMAND | MF_UNCHECKED);
        }
        CheckMenuItem(hMenu, id, MF_BYCOMMAND | MF_CHECKED);
        if (clothingNumber == 0) {
            clothingNumber = RandomRange(1, 12);
        }
        CLOTHING_NUMBER = clothingNumber;
        ExecAction(1);
    });
    pSprite->SetFrame(CLOTHES_A_3);
    pSprite->Show();
    ExecAction(1);

    int ret = pSprite->EventLoop();
    KillTimer(pSprite->GetHandle(), IDT_TRIGGER_ANIMATION);
    ReleaseSprite(pSprite);
    DeleteAnimationAction(CLOTHES_A_ACTION_BLINK);
    DeleteAnimationAction(CLOTHES_A_ACTION_1);
    DeleteAnimationAction(CLOTHES_A_ACTION_2);
    DeleteAnimationAction(CLOTHES_A_ACTION_3);
    DeleteAnimationAction(CLOTHES_A_ACTION_4);
    DeleteAnimationAction(CLOTHES_A_ACTION_5);
    DeleteAnimationAction(CLOTHES_B_ACTION_BLINK);
    DeleteAnimationAction(CLOTHES_B_ACTION_1);
    DeleteAnimationAction(CLOTHES_B_ACTION_2);
    DeleteAnimationAction(CLOTHES_B_ACTION_3);
    DeleteAnimationAction(CLOTHES_B_ACTION_4);
    DeleteAnimationAction(CLOTHES_B_ACTION_5);
    DeleteAnimationAction(CLOTHES_C_ACTION_BLINK);
    DeleteAnimationAction(CLOTHES_C_ACTION_1);
    DeleteAnimationAction(CLOTHES_C_ACTION_2);
    DeleteAnimationAction(CLOTHES_C_ACTION_3);
    DeleteAnimationAction(CLOTHES_C_ACTION_4);
    DeleteAnimationAction(CLOTHES_C_ACTION_5);
    DeleteAnimationAction(CLOTHES_D_ACTION_BLINK);
    DeleteAnimationAction(CLOTHES_D_ACTION_1);
    DeleteAnimationAction(CLOTHES_D_ACTION_2);
    DeleteAnimationAction(CLOTHES_D_ACTION_3);
    DeleteAnimationAction(CLOTHES_D_ACTION_4);
    DeleteAnimationAction(CLOTHES_D_ACTION_5);
    DeleteAnimationAction(CLOTHES_E_ACTION_BLINK);
    DeleteAnimationAction(CLOTHES_E_ACTION_1);
    DeleteAnimationAction(CLOTHES_E_ACTION_2);
    DeleteAnimationAction(CLOTHES_E_ACTION_3);
    DeleteAnimationAction(CLOTHES_E_ACTION_4);
    DeleteAnimationAction(CLOTHES_E_ACTION_5);
    DeleteAnimationAction(CLOTHES_F_ACTION_BLINK);
    DeleteAnimationAction(CLOTHES_F_ACTION_1);
    DeleteAnimationAction(CLOTHES_F_ACTION_2);
    DeleteAnimationAction(CLOTHES_F_ACTION_3);
    DeleteAnimationAction(CLOTHES_F_ACTION_4);
    DeleteAnimationAction(CLOTHES_F_ACTION_5);
    DeleteAnimationAction(CLOTHES_G_ACTION_BLINK);
    DeleteAnimationAction(CLOTHES_G_ACTION_1);
    DeleteAnimationAction(CLOTHES_G_ACTION_2);
    DeleteAnimationAction(CLOTHES_G_ACTION_3);
    DeleteAnimationAction(CLOTHES_G_ACTION_4);
    DeleteAnimationAction(CLOTHES_G_ACTION_5);
    DeleteAnimationAction(CLOTHES_H_ACTION_BLINK);
    DeleteAnimationAction(CLOTHES_H_ACTION_1);
    DeleteAnimationAction(CLOTHES_H_ACTION_2);
    DeleteAnimationAction(CLOTHES_H_ACTION_3);
    DeleteAnimationAction(CLOTHES_H_ACTION_4);
    DeleteAnimationAction(CLOTHES_H_ACTION_5);
    DeleteAnimationAction(CLOTHES_I_ACTION_BLINK);
    DeleteAnimationAction(CLOTHES_I_ACTION_1);
    DeleteAnimationAction(CLOTHES_I_ACTION_2);
    DeleteAnimationAction(CLOTHES_I_ACTION_3);
    DeleteAnimationAction(CLOTHES_I_ACTION_4);
    DeleteAnimationAction(CLOTHES_I_ACTION_5);
    DeleteAnimationAction(CLOTHES_J_ACTION_BLINK);
    DeleteAnimationAction(CLOTHES_J_ACTION_1);
    DeleteAnimationAction(CLOTHES_J_ACTION_2);
    DeleteAnimationAction(CLOTHES_J_ACTION_3);
    DeleteAnimationAction(CLOTHES_J_ACTION_4);
    DeleteAnimationAction(CLOTHES_J_ACTION_5);
    DeleteAnimationAction(CLOTHES_K_ACTION_BLINK);
    DeleteAnimationAction(CLOTHES_K_ACTION_1);
    DeleteAnimationAction(CLOTHES_K_ACTION_2);
    DeleteAnimationAction(CLOTHES_K_ACTION_3);
    DeleteAnimationAction(CLOTHES_K_ACTION_4);
    DeleteAnimationAction(CLOTHES_K_ACTION_5);
    DeleteAnimationAction(CLOTHES_L_ACTION_BLINK);
    DeleteAnimationAction(CLOTHES_L_ACTION_1);
    DeleteAnimationAction(CLOTHES_L_ACTION_2);
    DeleteAnimationAction(CLOTHES_L_ACTION_3);
    DeleteAnimationAction(CLOTHES_L_ACTION_4);
    DeleteAnimationAction(CLOTHES_L_ACTION_5);
    return ret;
}
