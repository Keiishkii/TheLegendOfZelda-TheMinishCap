#include "Pot.h"

#include <iostream>

#include "CollisionManager.h"
#include "SoundManager.h"

Pot::Pot(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag) : Entity(_pos, _textPos, _textName, _tag) 
{
	int collisionWidth = 24;
	int collisionHeight = 24;

	defaultCollisionBox = SDL_Rect{ 4, 4, collisionWidth, collisionHeight };
	collisionBox = defaultCollisionBox;

	collisionBox.x = defaultCollisionBox.x + position.x;
	collisionBox.y = defaultCollisionBox.y + position.y;

	CollisionManager::addSolidCollider(new SolidCollider(&collisionBox, UNIVERSAL, E_UNASIGNED, ID));
}

void Pot::update()
{

}

void Pot::death()
{
	GameplayState::removeObject(ID);
}

void Pot::lateUpdate()
{
	int healthChange;

	if (CollisionManager::checkDamageColliders(SDL_Rect(collisionBox), E_UNASIGNED, &healthChange))
	{
		SoundManager::playSound("MC_Shatter");
		death();
	}
}