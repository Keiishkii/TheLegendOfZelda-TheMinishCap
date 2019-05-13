#ifndef GAMEPLAYSTATE
#define GAMEPLAYSTATE

#include <SDL.h>
#include "Map.h"

#include "Player.h"

class GameplayState
{
private:
	static std::vector<GameObject * > objectList;
	static Map * currentMap;
	static int currentRoom;
	static int prevousRoom;
	static Player * player;
	static void updateEntities();
	static void loadMap();
	static void alignCamera();
public:
	static void loadState();
	static void update();
	static void display(SDL_Renderer** _renderer);
	static void addObjectToList(GameObject * _object);
};

#endif

