#include "Animation.h"

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

void DeleteAnimationAction(const ACTION *pAction)
{
    free((ACTION*)pAction);
}
