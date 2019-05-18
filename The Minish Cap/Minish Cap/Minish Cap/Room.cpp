#include "Room.h"

#include "CollisionManager.h"

// adds collision boxes to the collision list based on the walls within the room.
void Room::addRoomCollisions()
{
	// iterator for the rooms walls
	std::vector<SDL_Rect>::iterator itr = wallList.begin();
	
	// iterates through the list
	for (itr = wallList.begin(); itr < wallList.end(); itr++)
	{
		// creates a new rectangle so that it can be placed in the collision list
		SDL_Rect * wall = new SDL_Rect(*itr);
		wall->x += position.x;
		wall->y += position.y;

		// adds a solid colider based on the bounds of the wall
		CollisionManager::addSolidCollider(new SolidCollider(wall, UNIVERSAL, E_UNASIGNED, ID));
	}
}