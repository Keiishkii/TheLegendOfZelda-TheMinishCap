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

class SolidCollider
{
public:
	unsigned int IDGroup;

	SDL_Rect * boxBounds;
	CollisionType type;
	CollisionOrigin origin;

	SolidCollider(SDL_Rect * _boxBounds, CollisionType _type, CollisionOrigin _origin, unsigned int _ID) : boxBounds(_boxBounds), type(_type), origin(_origin), IDGroup(_ID) {}
};

class TriggerCollider
{
public:
	unsigned int IDGroup;

	SDL_Rect * boxBounds;
	CollisionType type;
	CollisionOrigin origin;

	TriggerCollider(SDL_Rect * _boxBounds, CollisionType _type, CollisionOrigin _origin, unsigned int _ID) : boxBounds(_boxBounds), type(_type), origin(_origin), IDGroup(_ID) {}
};

class DamageCollider
{
public:
	unsigned int IDGroup;

	SDL_Rect boxBounds;
	CollisionType type;
	CollisionOrigin origin;
	int damageValue = 0;

	DamageCollider(SDL_Rect _boxBounds, CollisionType _type, CollisionOrigin _origin, int _damageValue) : boxBounds(_boxBounds), type(_type), origin(_origin), damageValue(_damageValue) {}
};

#endif // !COLLISIONBOX
