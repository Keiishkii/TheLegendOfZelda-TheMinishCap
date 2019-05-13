#ifndef MAINMENUSTATE
#define MAINMENUSTATE

#include <SDL.h>
#include <vector>

#include "GameObject.h"

class TitleScreen
{
private:
	static std::vector<GameObject * > objectList;

	static void addObjectToList(GameObject * _object);
	static void inputs();
public:
	static void loadState();
	static void unloadState();
	static void update();
	static void display(SDL_Renderer** _renderer);
};

#endif

