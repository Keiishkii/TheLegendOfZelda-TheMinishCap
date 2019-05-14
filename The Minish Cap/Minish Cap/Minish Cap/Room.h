#ifndef ROOM
#define ROOM

#include <SDL.h>
#include <vector>

#include "GameObject.h"

class Room : public GameObject
{
private:
	std::vector<SDL_Rect> wallList;
	std::vector<GameObject *> respawningGameObjects;
	std::vector<GameObject *> singleSpawnGameObjects;
public:
	Room(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag, int _room) : GameObject(_pos, _textPos, _textName, _tag, _room) {}
	
	std::vector<GameObject *> * getRespawning() { return &respawningGameObjects; }
	std::vector<GameObject *> * getSingleSpawning() { return &singleSpawnGameObjects; }

	void addWall(SDL_Rect _wall) { wallList.push_back(_wall); }
	void addRespawning(GameObject * _gameObject) { respawningGameObjects.push_back(_gameObject); }
	void addSingleSpawning(GameObject * _gameObject) { singleSpawnGameObjects.push_back(_gameObject); }
	void addRoomCollisions();
};

#endif