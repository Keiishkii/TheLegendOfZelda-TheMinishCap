#ifndef TITLESCREENSWORD
#define TITLESCREENSWORD

#include <SDL.h>

#include "GameObject.h"

class TitleScreenSword : public GameObject
{
protected:
	int animationFrame = 0;
public:
	TitleScreenSword(SDL_Rect _pos);

	virtual void update() {}
	virtual void draw(SDL_Renderer ** _renderer);
};

#endif