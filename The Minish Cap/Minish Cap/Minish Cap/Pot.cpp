#include "Pot.h"

#include <iostream>

#include "CollisionManager.h"
#include "SoundManager.h"
#include "Rupee.h"

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
	int i = rand() % 100;

	if (i < 10)
	{
		SDL_Rect location = { position.x + ((position.w / 2) -7), position.y + ((position.h / 2) - 10), 14, 20 };
		GameplayState::addObjectToList(new Rupee(location, SDL_Rect{ 0,0, 7,10 }, "Rupees", TAG_GROUND_ENTITY, 20));
	}
	else if (i < 40)
	{
		SDL_Rect location = { position.x + ((position.w / 2) - 7), position.y + ((position.h / 2) - 10), 14, 20 };
		GameplayState::addObjectToList(new Rupee(location, SDL_Rect{ 0,0, 7,10 }, "Rupees", TAG_GROUND_ENTITY, 5));
	}
	else
	{
		SDL_Rect location = { position.x + ((position.w / 2) - 7), position.y + ((position.h / 2) - 10), 14, 20 };
		GameplayState::addObjectToList(new Rupee(location, SDL_Rect{ 0,0, 7,10 }, "Rupees", TAG_GROUND_ENTITY, 1));
	}

	SoundManager::playSound("MC_Rupee_Bounce");

	CollisionManager::removeCollider(ID);
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