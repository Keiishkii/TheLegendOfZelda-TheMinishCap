#include "Room.h"

#include "CollisionManager.h"

void Room::addRoomCollisions()
{
	std::vector<SDL_Rect>::iterator itr = wallList.begin();
	
	for (itr = wallList.begin(); itr < wallList.end(); itr++)
	{
		SDL_Rect * wall = new SDL_Rect(*itr);
		wall->x += position.x;
		wall->y += position.y;

		CollisionManager::addSolidCollider(new SolidCollider(wall, UNIVERSAL, E_UNASIGNED, ID));
	}
}