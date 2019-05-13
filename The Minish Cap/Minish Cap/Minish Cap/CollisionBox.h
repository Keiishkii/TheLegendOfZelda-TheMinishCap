#ifndef COLLISIONBOX
#define COLLISIONBOX

#include "SDL.h"

#include "GameObject.h"

enum CollisionType
{
	UNIVERSAL,
	PLAYER_ONLY,
	ENEMY_ONLY,
	UNIVERSAL_BUT_ENEMY,
	UNIVERSAL_BUT_PLAYER
};

enum CollisionOrigin 
{
	E_UNASIGNED,
	E_PLAYER,
	E_ENEMY
};

class CollisionBox
{
public:
	SDL_Rect * boxBounds;
	CollisionType type;
	CollisionOrigin origin;

	CollisionBox(SDL_Rect * _boxBounds, CollisionType _type, CollisionOrigin _origin) : boxBounds(_boxBounds), type(_type), origin(_origin) {}
};

#endif // !COLLISIONBOX
