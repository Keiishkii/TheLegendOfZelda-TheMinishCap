#include "Player.h"

#include <iostream>

#include "TextureManager.h"
#include "InputManager.h"

Player::Player(SDL_Rect _pos) : GameObject(_pos)
{
	renderTag = ENTITY;

	animationFrame = 0;
	
	int collisionWidth = 30;
	int collisionHeight = 22;

	xPos = position.x;
	yPos = position.y;

	defaultCollisionBox = SDL_Rect{18, 24, collisionWidth, collisionHeight };
	collisionBox = defaultCollisionBox;
	
	collisionBox.x = defaultCollisionBox.x + position.x;
	collisionBox.y = defaultCollisionBox.y + position.y;

	CollisionManager::addSolidCollider(new CollisionBox(&collisionBox, UNIVERSAL_BUT_PLAYER, E_PLAYER));

	textureName = "Link";
	texturePos = SDL_Rect{ 8, 3, 32, 32 };
}


void Player::update()
{
	getInput();
	processesStates();

	position.x = xPos;
	position.y = yPos;
}

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
		case ATTACKING:
		{
			currentSpeed = 0;
			attacking();
			break;
		}
	}
}

void Player::idle()
{

}

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
		
		if (!CollisionManager::checkSolidColliders(new CollisionBox(&collisionBox, UNIVERSAL_BUT_PLAYER, E_PLAYER)))
		{
			xPos += ((xVelocity / inputSpeed) * currentSpeed);
		}

		collisionBox.x = defaultCollisionBox.x + position.x;
		collisionBox.y = defaultCollisionBox.y + position.y + ((yVelocity / inputSpeed) * currentSpeed);

		if (!CollisionManager::checkSolidColliders(new CollisionBox(&collisionBox, UNIVERSAL_BUT_PLAYER, E_PLAYER)))
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

		if (!CollisionManager::checkSolidColliders(new CollisionBox(&collisionBox, UNIVERSAL_BUT_PLAYER, E_PLAYER)))
		{
			xPos += ((xVelocity / inputSpeed) * (currentSpeed));
		}

		collisionBox.x = defaultCollisionBox.x + position.x;
		collisionBox.y = defaultCollisionBox.y + position.y + ((yVelocity / inputSpeed) * currentSpeed);

		if (!CollisionManager::checkSolidColliders(new CollisionBox(&collisionBox, UNIVERSAL_BUT_PLAYER, E_PLAYER)))
		{
			yPos += ((yVelocity / inputSpeed) * currentSpeed);
		}

		break;
	}
	case EAST:
	{
		xVelocity = 1;

		collisionBox.y = defaultCollisionBox.y + position.y;
		collisionBox.x = defaultCollisionBox.x + position.x + (xVelocity * currentSpeed);
		
		if (!CollisionManager::checkSolidColliders(new CollisionBox(&collisionBox, UNIVERSAL_BUT_PLAYER, E_PLAYER)))
		{
			xPos += (xVelocity * currentSpeed);
		}

		break;
	}
	case WEST:
	{
		xVelocity = -1;

		collisionBox.y = defaultCollisionBox.y + position.y;
		collisionBox.x = defaultCollisionBox.x + position.x + (xVelocity * currentSpeed);

		if (!CollisionManager::checkSolidColliders(new CollisionBox(&collisionBox, UNIVERSAL_BUT_PLAYER, E_PLAYER)))
		{
			xPos += (xVelocity * currentSpeed);
		}

		break;
	}
	}
}

void Player::attacking()
{
	switch (direction)
	{
	case NORTH:
		break;
	case EAST:
		break;
	case SOUTH:
		break;
	case WEST:
		break;
	}
}

void Player::getInput()
{
	PlayerState prevousState = state;

	switch (state)
	{
		case IDLE:
		{
			if (InputManager::input.MouseLeftClicked)
			{
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
				state = ATTACKING;
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
	}

	if (state != prevousState)
		animationFrame = 0;
}

void Player::draw(SDL_Renderer ** _renderer)
{
	SDL_Rect offsetPosition = position;
	offsetPosition.x += Camera::xPositionOfset;
	offsetPosition.y += Camera::yPositionOfset;

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
		switch (direction)
		{
			case NORTH:
			{
				break;
			}
			case WEST:
			case EAST:
			{
				break;
			}
			case SOUTH:
			{
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

	if (direction == EAST)
		SDL_RenderCopyEx(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &offsetPosition, 0, NULL, (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL));
	else
		SDL_RenderCopy(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &offsetPosition);
}
