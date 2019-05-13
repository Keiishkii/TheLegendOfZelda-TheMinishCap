#ifndef TITLESCREENKEYWAIT
#define TITLESCREENKEYWAIT

#include <SDL.h>

#include "GameObject.h"

class TitleScreenKeyWait : public GameObject
{
protected:
	int animationFrame = 0;
public:
	TitleScreenKeyWait(SDL_Rect _pos);

	virtual void update() {}
	virtual void draw(SDL_Renderer ** _renderer);
};

#endif