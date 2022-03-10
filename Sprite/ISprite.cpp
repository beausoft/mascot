#include "ISprite.h"
#include "CSprite.h"

// 这是个工厂方法
EXPORT_API ISprite* CreateSprite(HINSTANCE hInstance, LPCWSTR spriteName, INT nWidth, INT nHeight, const OPTIONS* options)
{
	ISprite* pSprite = new CSprite(hInstance, spriteName, nWidth, nHeight, options);
	return pSprite;
}

EXPORT_API void ReleaseSprite(ISprite* pSprite)
{
	if (pSprite != NULL) {
		delete pSprite;
	}
}
