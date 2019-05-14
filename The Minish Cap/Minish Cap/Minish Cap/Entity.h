#ifndef ENTITY
#define ENTITY

#include "GameObject.h"
#include "GameplayState.h"

class Entity : public GameObject
{
protected:
	int health = 1;
	bool killable = false;

	SDL_Rect defaultCollisionBox;
	SDL_Rect collisionBox;
public:
	Entity(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag) : GameObject(_pos, _textPos, _textName, _tag) {}
	virtual void update() {}
	virtual void death();
};

#endif // !ENTITY
