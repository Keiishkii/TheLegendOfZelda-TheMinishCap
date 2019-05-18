#include "Rupee.h"

#include <iostream>

#include "CollisionManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "InventoryManager.h"

void triggerEntered(GameObject * _object, GameObject * _source);

Rupee::Rupee(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag, int _amount) : Entity(_pos, _textPos, _textName, _tag), amount(_amount)
{
	defaultCollisionBox = SDL_Rect{ 0, 0, 14, 20 };
	collisionBox = defaultCollisionBox;

	collisionBox.x = defaultCollisionBox.x + position.x;
	collisionBox.y = defaultCollisionBox.y + position.y;

	CollisionManager::addTriggerCollider(new TriggerCollider(&collisionBox, PLAYER_ONLY, E_UNASIGNED, ID, (triggerEntered), this));
}

void Rupee::update()
{

}

void Rupee::draw(SDL_Renderer ** _renderer)
{
	SDL_Rect offsetPosition = position;
	offsetPosition.x += Camera::xPositionOfset;
	offsetPosition.y += Camera::yPositionOfset;

	int animationLength = 15;

	switch (amount)
	{
	case 1:
	{
		if (animationFrame < animationLength)
		{
			texturePos = { 24, 0, 7, 10 };			
		}
		else if (animationFrame < animationLength * 2)
		{
			texturePos = { 32, 0, 7, 10 };
		}
		else if (animationFrame < animationLength * 3)
		{
			texturePos = { 40, 0, 7, 10 };
		}
		break;
	}
	case 5:
	{
		if (animationFrame < animationLength)
		{
			texturePos = { 48, 0, 7, 10 };
		}
		else if (animationFrame < animationLength * 2)
		{
			texturePos = { 56, 0, 7, 10 };
		}
		else if (animationFrame < animationLength * 3)
		{
			texturePos = { 64, 0, 7, 10 };
		}
		break;
	}
	case 20:
	{
		if (animationFrame < animationLength)
		{
			texturePos = { 0, 0, 7, 10 };
		}
		else if (animationFrame < animationLength * 2)
		{
			texturePos = { 8, 0, 7, 10 };
		}
		else if (animationFrame < animationLength * 3)
		{
			texturePos = { 16, 0, 7, 10 };
		}
		break;
	}
	}

	if (animationFrame > animationLength * 3)
	{
		animationFrame = 0;
	}
	else
	{
		animationFrame++;
	}

	SDL_RenderCopy(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &offsetPosition);
}

Rupee::~Rupee()
{

}

// function called when a rupee is picked up
void triggerEntered(GameObject * _object, GameObject * _source)
{
	GameplayState::removeObject((*_source).ID);
	SoundManager::playSound("MC_Rupee");
	InventoryManager::rupees += ((Rupee * )(_source))->getAmount();
	std::cout << "Rupees: " << InventoryManager::rupees << std::endl;
}