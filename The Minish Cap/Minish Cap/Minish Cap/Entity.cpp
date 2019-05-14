#include "Entity.h"

void Entity::death() 
{
	GameplayState::removeObject(ID);
}