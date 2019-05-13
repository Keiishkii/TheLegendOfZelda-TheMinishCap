#ifndef PLAYER
#define PLAYER

#include "CollisionManager.h"
#include "GameObject.h"

class Player : public GameObject
{
private:
	enum PlayerState
	{
		IDLE,
		WALKING,
		ROWLING,
		ATTACKING
	};

	enum PlayerDirection
	{
		NORTH,
		EAST,
		SOUTH,
		WEST
	};

	float xVelocity = 0;
	float yVelocity = 0;
	float currentSpeed = 0;

	int animationFrame;

	PlayerState state = IDLE;
	PlayerDirection direction = SOUTH;

	void rowling();
	void idle();
	void walking();
	void attacking();

	void attackSound();

	void getInput();
	void processesStates();
public:
	Player(SDL_Rect _pos);
	SDL_Rect defaultCollisionBox;
	SDL_Rect collisionBox;

	void draw(SDL_Renderer ** _renderer);
	void update();
};

#endif // !PLAYER
