#include "CollisionManager.h"

#include <iostream>

std::vector<SolidCollider * > CollisionManager::solidColliders;
std::vector<DamageCollider * > CollisionManager::damageColliders;
std::vector<TriggerCollider * > CollisionManager::triggerColliders;

bool CollisionManager::checkSolidColliders(SDL_Rect _colliderBox, CollisionOrigin _origin)
{
	bool collided = false;

	std::vector<SolidCollider *>::iterator itr = solidColliders.begin();

	for (itr = solidColliders.begin(); itr < solidColliders.end(); itr++)
	{
		switch (_origin)
		{
		case E_UNASIGNED:
		{
			if ((*itr)->type != PLAYER_ONLY && (*itr)->type != ENEMY_ONLY)
				if (SDL_HasIntersection((*itr)->boxBounds, &_colliderBox))
					collided = true;
			break;
		}
		case E_ENEMY:
		{
			if ((*itr)->type != UNIVERSAL_BUT_ENEMY && (*itr)->type != PLAYER_ONLY)
				if (SDL_HasIntersection((*itr)->boxBounds, &_colliderBox))
					collided = true;
			break;
		}
		case E_PLAYER:
		{
			if ((*itr)->type != UNIVERSAL_BUT_PLAYER && (*itr)->type != ENEMY_ONLY)
				if (SDL_HasIntersection((*itr)->boxBounds, &_colliderBox))
					collided = true;
			break;
		}
		}

		if (collided)
			break;
	}

	return collided;
}

bool CollisionManager::checkTriggerColliders(SDL_Rect _colliderBox, CollisionOrigin _origin, GameObject * _triggeredObject)
{
	bool collided = false;

	std::vector<TriggerCollider *>::iterator itr = triggerColliders.begin();

	for (itr = triggerColliders.begin(); itr < triggerColliders.end(); itr++)
	{
		switch (_origin)
		{
		case E_UNASIGNED:
		{
			if ((*itr)->type != PLAYER_ONLY && (*itr)->type != ENEMY_ONLY)
				if (SDL_HasIntersection((*itr)->boxBounds, &_colliderBox))
				{
					(*itr)->triggerFunction(_triggeredObject, (*itr)->source);
					collided = true;
				}
			break;
		}
		case E_ENEMY:
		{
			if ((*itr)->type != UNIVERSAL_BUT_ENEMY && (*itr)->type != PLAYER_ONLY)
				if (SDL_HasIntersection((*itr)->boxBounds, &_colliderBox))
				{
					(*itr)->triggerFunction(_triggeredObject, (*itr)->source);
					collided = true;
				}
			break;
		}
		case E_PLAYER:
		{
			if ((*itr)->type != UNIVERSAL_BUT_PLAYER && (*itr)->type != ENEMY_ONLY)
				if (SDL_HasIntersection((*itr)->boxBounds, &_colliderBox))
				{
					(*itr)->triggerFunction(_triggeredObject, (*itr)->source);
					collided = true;
				}
			break;
		}
		}

		if (collided)
			break;
	}

	return collided;
}

bool CollisionManager::checkDamageColliders(SDL_Rect _colliderBox, CollisionOrigin _origin, int * _healthEffect)
{
	bool collided = false;
	*_healthEffect = 0;

	std::vector<DamageCollider *>::iterator itr = damageColliders.begin();

	for (itr = damageColliders.begin(); itr < damageColliders.end(); itr++)
	{
		switch (_origin)
		{
		case E_UNASIGNED:
		{
			if ((*itr)->type != PLAYER_ONLY && (*itr)->type != ENEMY_ONLY)
				if (SDL_HasIntersection(&(*itr)->boxBounds, &_colliderBox))
				{
					collided = true;
					*_healthEffect = (*itr)->damageValue;
				}
			break;
		}
		case E_ENEMY:
		{
			if ((*itr)->type != UNIVERSAL_BUT_ENEMY && (*itr)->type != PLAYER_ONLY)
				if (SDL_HasIntersection(&(*itr)->boxBounds, &_colliderBox))
				{
					collided = true;
					*_healthEffect = (*itr)->damageValue;
				}
			break;
		}
		case E_PLAYER:
		{
			if ((*itr)->type != UNIVERSAL_BUT_PLAYER && (*itr)->type != ENEMY_ONLY)
				if (SDL_HasIntersection(&(*itr)->boxBounds, &_colliderBox))
				{
					collided = true;
					*_healthEffect = (*itr)->damageValue;
				}
			break;
		}
		}

		if (collided)
			break;
	}

	return collided;
}

void CollisionManager::removeTriggerCollider(int _ID)
{
	std::vector<TriggerCollider * >::iterator trigItr = triggerColliders.begin();

	for (trigItr = triggerColliders.begin(); trigItr < triggerColliders.end(); trigItr++)
	{
		if ((*trigItr)->IDGroup == _ID)
		{
			delete *trigItr;
			trigItr = triggerColliders.erase(trigItr);
		}
	}
}

void CollisionManager::removeCollider(int _ID)
{
	std::vector<SolidCollider * >::iterator solidItr = solidColliders.begin();

	for (solidItr = solidColliders.begin(); solidItr < solidColliders.end(); solidItr++)
	{
		if ((*solidItr)->IDGroup == _ID)
		{
			delete *solidItr;
			solidItr = solidColliders.erase(solidItr);
		}
	}
}

void CollisionManager::clearFrameColliders()
{
	std::vector<DamageCollider * >::iterator damageItr = damageColliders.begin();

	for (damageItr = damageColliders.begin(); damageItr < damageColliders.end(); damageItr++)
	{
		delete *damageItr;
	}

	damageColliders.clear();
}

void CollisionManager::clearColliders()
{
	std::vector<TriggerCollider * >::iterator trigItr = triggerColliders.begin();

	for (trigItr = triggerColliders.begin(); trigItr < triggerColliders.end(); trigItr++)
	{
		delete *trigItr;
	}

	triggerColliders.clear();
	std::vector<DamageCollider * >::iterator damageItr = damageColliders.begin();

	for (damageItr = damageColliders.begin(); damageItr < damageColliders.end(); damageItr++)
	{
		delete *damageItr;
	}

	damageColliders.clear();
	std::vector<SolidCollider * >::iterator solidItr = solidColliders.begin();

	for (solidItr = solidColliders.begin(); solidItr < solidColliders.end(); solidItr++)
	{
		delete *solidItr;
	}

	solidColliders.clear();
}