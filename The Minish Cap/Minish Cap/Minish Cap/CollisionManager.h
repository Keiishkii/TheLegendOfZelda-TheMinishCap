#ifndef COLLISIONMANAGER
#define COLLISIONMANAGER

#include <vector>

#include "SDL.h"

#include "CollisionBox.h"


class CollisionManager
{
private:
	static std::vector<CollisionBox *> solidColliders;
public:
	static void addSolidCollider(CollisionBox * _collider) { solidColliders.push_back(_collider); };

	static bool checkSolidColliders(CollisionBox * _collider);

	static void clearColliders();
};

#endif // !COLLISIONMANAGER
