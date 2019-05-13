#ifndef STATE_MANAGER
#define STATE_MANAGER

#include <SDL.h>

class StateManager
{
private:

public:
	static void update(SDL_Window** window, SDL_Renderer** renderer);
};

#endif