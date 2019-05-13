#ifndef ROOM
#define ROOM

#include <SDL.h>
#include <vector>

#include "GameObject.h"

class Room : public GameObject
{
private:
	std::vector<SDL_Rect> wallList;
public:
	Room(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag, int _room) : GameObject(_pos, _textPos, _textName, _tag, _room) {}
	void addWall(SDL_Rect _wall) { wallList.push_back(_wall); }
	void addRoomCollisions();
};

#endif