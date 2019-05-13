#ifndef TITILESCREENLIGHTRAYS
#define TITILESCREENLIGHTRAYS

#include <string>
#include <SDL.h>

#include "GameObject.h"

class TitleScreenLightRays : public GameObject
{
private:
	int animationFrame = 0;
public:
	TitleScreenLightRays(SDL_Rect _pos);

	void update() {}
	void draw(SDL_Renderer ** _renderer);
};

#endif