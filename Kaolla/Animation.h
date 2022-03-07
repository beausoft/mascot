#pragma once
#include<Windows.h>

struct FRAME {
	int idBitmap;
	int offsetX;
	int offsetY;
};

struct ACTION {
	BOOL loop;
	UINT sound;
	int interval;
	int length;
	FRAME frames[1];
};

struct AnimationStatus {
	BOOL running;
	const ACTION* action;
	int frameIndex;
};

const ACTION* CreateAnimationAction(const FRAME* frames, int framesLength, int interval, UINT sound, BOOL loop);
void DeleteAnimationAction(const ACTION *pAction);
