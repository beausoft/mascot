#include "../Sprite/ISprite.h"
#include "resource.h"
#include <cstdlib>

constexpr auto IDT_TRIGGER_ANIMATION = 10001;

const ACTION* CreateAnimationAction(const FRAME* frames, int framesLength, int interval, UINT sound, BOOL loop)
{
    ACTION* action = (ACTION*)malloc(sizeof(ACTION) + framesLength * sizeof(FRAME));
    // �ж��ڴ��Ƿ�����ɹ�
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

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    MessageBox(NULL, L"Hello World", L"��ʾ", MB_OK);
}
