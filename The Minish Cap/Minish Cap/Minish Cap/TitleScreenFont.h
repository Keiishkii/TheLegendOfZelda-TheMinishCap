#ifndef TITLESCREENFONT
#define TITLESCREENFONT

#include <SDL.h>

#include "GameObject.h"

class TitleScreenFont : public GameObject
{
protected:
	bool triggerSoundPlayed = false;
	int animationFrame = 0;
public:
	TitleScreenFont(SDL_Rect _pos);

	virtual void update();
	virtual void draw(SDL_Renderer ** _renderer);
};

#endif