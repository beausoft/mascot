#include <Windows.h>
#include "../Sprite/ISprite.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	OPTIONS options;
	ISprite * pSprite = CreateSprite(hInstance, L"Mei", 100, 100, &options);

	pSprite->Show();
	int ret = pSprite->EventLoop();

	ReleaseSprite(pSprite);

	return ret;
}