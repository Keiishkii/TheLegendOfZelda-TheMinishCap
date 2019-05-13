#include "CollisionManager.h"

#include "Debug.h"

std::vector<CollisionBox * > CollisionManager::solidColliders;

bool CollisionManager::checkSolidColliders(CollisionBox * _collider)
{
	bool collided = false;

	std::vector<CollisionBox *>::iterator itr = solidColliders.begin();
	
	for (itr = solidColliders.begin(); itr < solidColliders.end(); itr++)
	{
		switch (_collider->origin)
			{
			case E_UNASIGNED:
			{
				if ((*itr)->type != PLAYER_ONLY && (*itr)->type != ENEMY_ONLY)
					if (SDL_HasIntersection((*itr)->boxBounds, _collider->boxBounds))
						collided = true;
				break;
			}
			case E_ENEMY:
			{
				if ((*itr)->type != UNIVERSAL_BUT_ENEMY && (*itr)->type != PLAYER_ONLY)
					if (SDL_HasIntersection((*itr)->boxBounds, _collider->boxBounds))
						collided = true;
				break;
			}
			case E_PLAYER:
			{
				if ((*itr)->type != UNIVERSAL_BUT_PLAYER && (*itr)->type != ENEMY_ONLY)
					if (SDL_HasIntersection((*itr)->boxBounds, _collider->boxBounds))
						collided = true;
				break;
			}
		}

		if (collided)
			break;
	}

	delete _collider;

	return collided;
}

void CollisionManager::clearColliders()
{
	std::vector<CollisionBox * >::iterator solidItr = solidColliders.begin();

	for (solidItr = solidColliders.begin(); solidItr < solidColliders.end(); solidItr++)
	{
		delete *solidItr;
	}

	solidColliders.clear();
}