#ifndef COLLISIONMANAGER
#define COLLISIONMANAGER

#include <vector>

#include "SDL.h"

#include "CollisionBox.h"


class CollisionManager
{
private:
	static std::vector<SolidCollider *> solidColliders;
	static std::vector<DamageCollider *> damageColliders;
	static std::vector<TriggerCollider *> triggerColliders;
public:
	static void addSolidCollider(SolidCollider * _collider) { solidColliders.push_back(_collider); };
	static void addDamageCollider(DamageCollider * _collider) { damageColliders.push_back(_collider); };
	static void addTriggerCollider(TriggerCollider * _collider) { triggerColliders.push_back(_collider); };

	static bool checkSolidColliders(SDL_Rect _colliderBox, CollisionOrigin _origin);
	static bool checkDamageColliders(SDL_Rect _colliderBox, CollisionOrigin _origin, int * _health);

	static void clearFrameColliders();

	static void clearColliders();
};

#endif // !COLLISIONMANAGER
