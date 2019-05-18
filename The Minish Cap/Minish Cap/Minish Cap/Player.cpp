#include "Player.h"

#include <iostream>

#include "TextureManager.h"
#include "InputManager.h"
#include "SoundManager.h"

//constructor
Player::Player(SDL_Rect _pos) : GameObject(_pos)
{
	renderTag = TAG_ENTITY;

	animationFrame = 0;
	
	int collisionWidth = 18;
	int collisionHeight = 32;

	xPos = position.x;
	yPos = position.y;

	defaultCollisionBox = SDL_Rect{24, 24, collisionWidth, collisionHeight };
	collisionBox = defaultCollisionBox;
	
	collisionBox.x = defaultCollisionBox.x + position.x;
	collisionBox.y = defaultCollisionBox.y + position.y;

	CollisionManager::addSolidCollider(new SolidCollider(&collisionBox, UNIVERSAL_BUT_PLAYER, E_PLAYER, ID));

	textureName = "Link";
	texturePos = SDL_Rect{ 8, 3, 32, 32 };
}

// updates the player based there inputs and states
void Player::update()
{
	getInput();

	processesStates();

	position.x = xPos;
	position.y = yPos;
}

// checks damage after damage colliders where added in the gameObjects updates
void Player::lateUpdate()
{
	CollisionManager::checkTriggerColliders(SDL_Rect(collisionBox), E_PLAYER, this);
	damageCheck();
}

// checks to see if the player has taken damage.
void Player::damageCheck()
{
	int healthChange;

	if (!invunrable)
	{
		if (CollisionManager::checkDamageColliders(SDL_Rect(collisionBox), E_PLAYER, &healthChange))
		{
			invunrable = true;
		}
	}
	else if (invunrabiltyFrames < 60)
	{
		invunrabiltyFrames++;
	}
	else
	{
		invunrable = false;
		invunrabiltyFrames = 0;
	}
}

// selects and calls the behavour to run based on the current state
void Player::processesStates()
{
	switch (state)
	{
		case IDLE:
		{
			currentSpeed = 0;
			idle();
			break;
		}
		case WALKING:
		{
			currentSpeed = 2;
			walking();
			break;
		}
		case ROWLING:
		{
			currentSpeed = 5;
			rowling();
			break;
		}
		case ATTACKING:
		{
			currentSpeed = 0;
			attacking();
			break;
		}
	}
}

// Idle behavour
void Player::idle()
{

}

// Walking behavour
void Player::walking()
{
	switch (direction)
	{
	case NORTH:
	{
		xVelocity = 0;
		yVelocity = -1;

		if (InputManager::input.KeyADown || InputManager::input.KeyLeftDown)
		{
			xVelocity = -1;
		}

		if (InputManager::input.KeyDDown || InputManager::input.KeyRightDown)
		{
			xVelocity = 1;
		}

		float inputSpeed = sqrt(pow(xVelocity, 2) + pow(yVelocity, 2));
		collisionBox.y = defaultCollisionBox.y + position.y;
		collisionBox.x = defaultCollisionBox.x + position.x + ((xVelocity / inputSpeed) * currentSpeed);
		
		if (!CollisionManager::checkSolidColliders(collisionBox, E_PLAYER))
		{
			xPos += ((xVelocity / inputSpeed) * currentSpeed);
		}

		collisionBox.x = defaultCollisionBox.x + position.x;
		collisionBox.y = defaultCollisionBox.y + position.y + ((yVelocity / inputSpeed) * currentSpeed);

		if (!CollisionManager::checkSolidColliders(collisionBox, E_PLAYER))
		{
			yPos += ((yVelocity / inputSpeed) * currentSpeed);
		}

		break;
	}
	case SOUTH:
	{
		xVelocity = 0;
		yVelocity = 1;

		if (InputManager::input.KeyADown || InputManager::input.KeyLeftDown)
		{
			xVelocity = -1;
		}

		if (InputManager::input.KeyDDown || InputManager::input.KeyRightDown)
		{
			xVelocity = 1;
		}

		float inputSpeed = sqrt(pow(xVelocity, 2) + pow(yVelocity, 2));
		collisionBox.y = defaultCollisionBox.y + position.y;
		collisionBox.x = defaultCollisionBox.x + position.x + ((xVelocity / inputSpeed) * currentSpeed);

		if (!CollisionManager::checkSolidColliders(collisionBox, E_PLAYER))
		{
			xPos += ((xVelocity / inputSpeed) * (currentSpeed));
		}

		collisionBox.x = defaultCollisionBox.x + position.x;
		collisionBox.y = defaultCollisionBox.y + position.y + ((yVelocity / inputSpeed) * currentSpeed);

		if (!CollisionManager::checkSolidColliders(collisionBox, E_PLAYER))
		{
			yPos += ((yVelocity / inputSpeed) * currentSpeed);
		}

		break;
	}
	case EAST:
	{
		yVelocity = 0;
		xVelocity = 1;

		collisionBox.y = defaultCollisionBox.y + position.y;
		collisionBox.x = defaultCollisionBox.x + position.x + (xVelocity * currentSpeed);

		if (!CollisionManager::checkSolidColliders(collisionBox, E_PLAYER))
		{
			xPos += (xVelocity * currentSpeed);
		}

		break;
	}
	case WEST:
	{
		yVelocity = 0;
		xVelocity = -1;

		collisionBox.y = defaultCollisionBox.y + position.y;
		collisionBox.x = defaultCollisionBox.x + position.x + (xVelocity * currentSpeed);

		if (!CollisionManager::checkSolidColliders(collisionBox, E_PLAYER))
		{
			xPos += (xVelocity * currentSpeed);
		}

		break;
	}
	}
}

// Rowling behavour
void Player::rowling()
{
	float inputSpeed = sqrt(pow(xVelocity, 2) + pow(yVelocity, 2));
	collisionBox.y = defaultCollisionBox.y + position.y;
	collisionBox.x = defaultCollisionBox.x + position.x + ((xVelocity / inputSpeed) * currentSpeed);

	if (!CollisionManager::checkSolidColliders(collisionBox, E_PLAYER))
	{
		xPos += ((xVelocity / inputSpeed) * currentSpeed);
	}

	collisionBox.x = defaultCollisionBox.x + position.x;
	collisionBox.y = defaultCollisionBox.y + position.y + ((yVelocity / inputSpeed) * currentSpeed);

	if (!CollisionManager::checkSolidColliders(collisionBox, E_PLAYER))
	{
		yPos += ((yVelocity / inputSpeed) * currentSpeed);
	}
}

// Attacking behavour
void Player::attacking()
{
	int animationLength = 2;

	SDL_Rect collider = { 0, 0, 16, 16 };

	collider.x = defaultCollisionBox.x + position.x + (defaultCollisionBox.x / 2);
	collider.y = defaultCollisionBox.y + position.y + (defaultCollisionBox.y / 2);

	switch (direction)
	{
	case NORTH:
		if (animationFrame < animationLength)
		{
			collider.x += 21;
			collider.y += -19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 2)
		{
			collider.x += 17;
			collider.y += -21;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 3)
		{
			collider.x += 13;
			collider.y += -23;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 4)
		{
			collider.x += 9;
			collider.y += -24;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 5)
		{
			collider.x += 5;
			collider.y += -25;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 6)
		{
			collider.x += 1;
			collider.y += -26;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 7)
		{
			collider.x += -3;
			collider.y += -25;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 8)
		{
			collider.x += -7;
			collider.y += -24;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 9)
		{
			collider.x += -11;
			collider.y += -23;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 10)
		{
			collider.x += -15;
			collider.y += -21;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 11)
		{
			collider.x += -19;
			collider.y += -19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		break;
	case EAST:
		if (animationFrame < animationLength)
		{
			collider.x += -19;
			collider.y += 19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 2)
		{
			collider.x += -19;
			collider.y += 19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 3)
		{
			collider.x += -19;
			collider.y += 19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 4)
		{
			collider.x += -19;
			collider.y += 19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 5)
		{
			collider.x += -19;
			collider.y += 19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 6)
		{
			collider.x += -19;
			collider.y += 19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 7)
		{
			collider.x += -19;
			collider.y += 19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 8)
		{
			collider.x += -19;
			collider.y += 19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 9)
		{
			collider.x += -19;
			collider.y += 19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 10)
		{
			collider.x += -19;
			collider.y += 19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		break;
	case SOUTH:
		if (animationFrame < animationLength)
		{
			collider.x += -19;
			collider.y += 19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 2)
		{
			collider.x += -15;
			collider.y += 21;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 3)
		{
			collider.x += -11;
			collider.y += 23;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 4)
		{
			collider.x += -7;
			collider.y += 24;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 5)
		{
			collider.x += -3;
			collider.y += 25;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 6)
		{
			collider.x += 1;
			collider.y += 26;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 7)
		{
			collider.x += 5;
			collider.y += 25;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 8)
		{
			collider.x += 9;
			collider.y += 24;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 9)
		{
			collider.x += 13;
			collider.y += 23;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 10)
		{
			collider.x += 17;
			collider.y += 21;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		else if (animationFrame < animationLength * 11)
		{
			collider.x += 21;
			collider.y += 19;
			CollisionManager::addDamageCollider(new DamageCollider(collider, UNIVERSAL_BUT_PLAYER, E_PLAYER, 4));
		}
		break;
	case WEST:
		if (animationFrame < animationLength)
		{
		}
		else if (animationFrame < animationLength * 2)
		{
		}
		else if (animationFrame < animationLength * 3)
		{
		}
		else if (animationFrame < animationLength * 4)
		{
		}
		else if (animationFrame < animationLength * 5)
		{
		}
		else if (animationFrame < animationLength * 6)
		{
		}
		else if (animationFrame < animationLength * 7)
		{
		}
		else if (animationFrame < animationLength * 8)
		{
		}
		else if (animationFrame < animationLength * 9)
		{
		}
		else if (animationFrame < animationLength * 10)
		{
		}
		break;
	}
}

// Changes the players state based on there inputs and the state the character is currently in
void Player::getInput()
{
	PlayerState prevousState = state;

	switch (state)
	{
		case IDLE:
		{
			if (InputManager::input.MouseLeftClicked)
			{
				attackSound();
				state = ATTACKING;
			}
			else if (InputManager::input.KeyWDown || InputManager::input.KeyUpDown)
			{
				state = WALKING;
				direction = NORTH;
			}
			else if (InputManager::input.KeySDown || InputManager::input.KeyDownDown)
			{
				state = WALKING;
				direction = SOUTH;
			}
			else if (InputManager::input.KeyADown || InputManager::input.KeyLeftDown)
			{
				state = WALKING;
				direction = WEST;
			}
			else if (InputManager::input.KeyDDown || InputManager::input.KeyRightDown)
			{
				state = WALKING;
				direction = EAST;
			}
			break;
		}
		case WALKING:
		{
			if (InputManager::input.MouseLeftClicked)
			{
				attackSound();
				state = ATTACKING;
			}
			else if (InputManager::input.KeySpacePressed)
			{
				attackSound();
				state = ROWLING;
			}
			else if (InputManager::input.KeyWDown || InputManager::input.KeyUpDown)
			{
				direction = NORTH;
			}
			else if (InputManager::input.KeySDown || InputManager::input.KeyDownDown)
			{
				direction = SOUTH;
			}
			else if (InputManager::input.KeyADown || InputManager::input.KeyLeftDown)
			{
				direction = WEST;
			}
			else if (InputManager::input.KeyDDown || InputManager::input.KeyRightDown)
			{
				direction = EAST;
			}
			else
			{
				state = IDLE;
			}
			break;
		}
		case ATTACKING:
		{
			int animationLength = 2;

			if (InputManager::input.MouseLeftClicked)
			{
				attackSound();
				animationFrame = 0;
			}
			else if (direction == WEST || direction == EAST)
			{
				if (animationFrame >= animationLength * 10)
					state = IDLE;
			}
			else if (animationFrame >= animationLength * 11)
				state = IDLE;
			break;
		}
		case ROWLING:
		{
			int animationLength = 3;

			if (direction == WEST || direction == EAST)
			{
				if (animationFrame >= animationLength * 7)
					state = IDLE;
			}
			else if (animationFrame >= animationLength * 8)
				state = IDLE;
			break;
		}
	}

	if (state != prevousState)
		animationFrame = 0;
}

void Player::attackSound()
{
	int random = rand() % 100;

	if (random < 33)
		SoundManager::playSound("MC_Link_Sword1");
	else if (random < 66)
		SoundManager::playSound("MC_Link_Sword2");
	else
		SoundManager::playSound("MC_Link_Sword3");
}

// draws the sprite with its current texutre position to the renderer
void Player::draw(SDL_Renderer ** _renderer)
{
	SDL_Rect offsetPosition = position;
	offsetPosition.x += Camera::xPositionOfset;
	offsetPosition.y += Camera::yPositionOfset;

	// changes the animation texture based on the players state and the animation frame
	switch (state)
	{
	case IDLE:
	{
		switch (direction)
		{
			case NORTH:
			{
				texturePos = { 72, 3, 32, 32 };
				break;
			}
			case WEST:
			case EAST:
			{
				texturePos = { 40, 3, 32, 32 };
				break;
			}
			case SOUTH:
			{
				texturePos = {8, 3, 32, 32};
				break;
			}
		}
		break;
	}
	case WALKING:
	{
		int animationLength = 5;

		switch (direction)
		{
			case NORTH:
			{
				if (animationFrame < animationLength)
				{
					texturePos = { 676, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 2)
				{
					texturePos = { 708, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 3)
				{
					texturePos = { 740, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 4)
				{
					texturePos = { 772, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 5)
				{
					texturePos = { 804, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 6)
				{
					texturePos = { 836, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 7)
				{
					texturePos = { 868, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 8)
				{
					texturePos = { 900, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 9)
				{
					texturePos = { 932, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 10)
				{
					texturePos = { 964, 71, 32, 32 };
				}
				else
				{
					animationFrame = 0;
				}
				break;
			}
			case WEST:
			case EAST:
			{
				if (animationFrame < animationLength)
				{
					texturePos = { 341, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 2)
				{
					texturePos = { 373, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 3)
				{
					texturePos = { 405, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 4)
				{
					texturePos = { 437, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 5)
				{
					texturePos = { 469, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 6)
				{
					texturePos = { 501, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 7)
				{
					texturePos = { 533, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 8)
				{
					texturePos = { 565, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 9)
				{
					texturePos = { 597, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 10)
				{
					texturePos = { 629, 71, 32, 32 };
				}
				else
				{
					animationFrame = 0;
				}
				break;
			}
			case SOUTH:
			{
				if (animationFrame < animationLength)
				{
					texturePos = { 8, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 2)
				{
					texturePos = { 40, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 3)
				{
					texturePos = { 72, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 4)
				{
					texturePos = { 104, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 5)
				{
					texturePos = { 136, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 6)
				{
					texturePos = { 168, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 7)
				{
					texturePos = { 200, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 8)
				{
					texturePos = { 232, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 9)
				{
					texturePos = { 264, 71, 32, 32 };
				}
				else if (animationFrame < animationLength * 10)
				{
					texturePos = { 296, 71, 32, 32 };
				}
				else
				{
					animationFrame = 0;
				}
				break;
			}
		}
		break;
	}
	case ROWLING:
	{
		int animationLength = 3;

		switch (direction)
		{
			case NORTH:
			{
				if (animationFrame < animationLength)
				{
					texturePos = { 528, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 2)
				{
					texturePos = { 560, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 3)
				{
					texturePos = { 592, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 4)
				{
					texturePos = { 624, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 5)
				{
					texturePos = { 656, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 6)
				{
					texturePos = { 688, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 7)
				{
					texturePos = { 720, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 8)
				{
					texturePos = { 752, 1100, 32, 32 };
				}
				break;
			}
			case WEST:
			case EAST:
			{
				if (animationFrame < animationLength)
				{
					texturePos = { 284, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 2)
				{
					texturePos = { 316, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 3)
				{
					texturePos = { 348, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 4)
				{
					texturePos = { 380, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 5)
				{
					texturePos = { 412, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 6)
				{
					texturePos = { 444, 1100, 32, 32 };
				}
				else if (animationFrame < animationLength * 7)
				{
					texturePos = { 476, 1100, 32, 32 };
				}
				break;
			}
			case SOUTH:
			{
				if (animationFrame < animationLength)
				{
					texturePos = { 12, 1097, 32, 32 };
				}
				else if (animationFrame < animationLength * 2)
				{
					texturePos = { 44, 1097, 32, 32 };
				}
				else if (animationFrame < animationLength * 3)
				{
					texturePos = { 76, 1097, 32, 32 };
				}
				else if (animationFrame < animationLength * 4)
				{
					texturePos = { 108, 1097, 32, 32 };
				}
				else if (animationFrame < animationLength * 5)
				{
					texturePos = { 140, 1097, 32, 32 };
				}
				else if (animationFrame < animationLength * 6)
				{
					texturePos = { 172, 1097, 32, 32 };
				}
				else if (animationFrame < animationLength * 7)
				{
					texturePos = { 204, 1097, 32, 32 };
				}
				else if (animationFrame < animationLength * 8)
				{
					texturePos = { 236, 1097, 32, 32 };
				}
				break;
			}
		}
		break;
	}
	case ATTACKING:
	{
		int animationLength = 2;

		switch (direction)
		{
			case NORTH:
			{
				if (animationFrame < animationLength)
				{
					texturePos = { 719, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 2)
				{
					texturePos = { 751, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 3)
				{
					texturePos = { 783, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 4)
				{
					texturePos = { 815, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 5)
				{
					texturePos = { 847, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 6)
				{
					texturePos = { 879, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 7)
				{
					texturePos = { 911, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 8)
				{
					texturePos = { 943, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 9)
				{
					texturePos = { 975, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 10)
				{
					texturePos = { 1007, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 11)
				{
					texturePos = { 1039, 342, 32, 32 };
				}
				break;
			}
			case WEST:
			case EAST:
			{
				if (animationFrame < animationLength)
				{
					texturePos = { 375, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 2)
				{
					texturePos = { 407, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 3)
				{
					texturePos = { 439, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 4)
				{
					texturePos = { 471, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 5)
				{
					texturePos = { 503, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 6)
				{
					texturePos = { 535, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 7)
				{
					texturePos = { 567, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 8)
				{
					texturePos = { 599, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 9)
				{
					texturePos = { 631, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 10)
				{
					texturePos = { 663, 342, 32, 32 };
				}
				break;
			}
			case SOUTH:
			{
				if (animationFrame < animationLength)
				{
					texturePos = { 8, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 2)
				{
					texturePos = { 40, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 3)
				{
					texturePos = { 72, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 4)
				{
					texturePos = { 104, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 5)
				{
					texturePos = { 136, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 6)
				{
					texturePos = { 168, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 7)
				{
					texturePos = { 200, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 8)
				{
					texturePos = { 232, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 9)
				{
					texturePos = { 264, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 10)
				{
					texturePos = { 296, 342, 32, 32 };
				}
				else if (animationFrame < animationLength * 11)
				{
					texturePos = { 328, 342, 32, 32 };
				}
				break;
			}
			}		
		}
		break;
	}
	
	if (animationFrame < 0)
		animationFrame;
	else
		animationFrame++;

	// flips the sprite if the animation is facing east
	if (direction == EAST)
		SDL_RenderCopyEx(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &offsetPosition, 0, NULL, (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL));
	else
		SDL_RenderCopy(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &offsetPosition);
}
