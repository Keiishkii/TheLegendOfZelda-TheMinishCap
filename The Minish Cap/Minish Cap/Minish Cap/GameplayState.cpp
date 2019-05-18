#include "GameplayState.h"

#include <iostream>

#include "SoundManager.h"
#include "GameManager.h"
#include "MapManager.h"
#include "InputManager.h"
#include "InventoryManager.h"

#include "Camera.h"

std::vector<GameObject * > GameplayState::objectList;
std::vector<int> GameplayState::objectToRemove;

Map * GameplayState::currentMap = nullptr;

Player * GameplayState::player = nullptr;

int GameplayState::currentRoom = 0;
int GameplayState::prevousRoom = 0;

// ran on start of the states initialisation
void GameplayState::loadState()
{
	// emptys the object list
	objectList.clear();
	GameManager::gameState = GAMEPLAY;

	// gets the current map and room
	if (currentMap == nullptr)
	{
		if (GameManager::loadedSave != nullptr)
		{
			currentMap = MapManager::getMap((*GameManager::loadedSave).getMap());
			prevousRoom = (*MapManager::getMap((*GameManager::loadedSave).getMap())).defaultRoom;
			currentRoom = (*MapManager::getMap((*GameManager::loadedSave).getMap())).defaultRoom;
		}
	}

	// creates the player if it is equal to null
	if (player == nullptr)
	{
		player = new Player(SDL_Rect{currentMap->defaultX, currentMap->defaultY, 64, 64});
	}
	
	addObjectToList(player);

	std::vector<GameObject * >::iterator itr = (*currentMap->getRoomList()->at(currentRoom - 1)->getRespawning()).begin();

	// adds the respawning items to the games list
	for (itr = (*currentMap->getRoomList()->at(currentRoom - 1)->getRespawning()).begin(); itr < (*currentMap->getRoomList()->at(currentRoom - 1)->getRespawning()).end(); itr++)
	{
		addObjectToList(*itr);
	}

	InventoryManager::maxHealth = GameManager::loadedSave->getMaxHealth();
	InventoryManager::currentHealth = GameManager::loadedSave->getCurrentHealth();
	InventoryManager::rupees = GameManager::loadedSave->getRupees();
	InventoryManager::bombs = GameManager::loadedSave->getBombs();
	InventoryManager::arrows = GameManager::loadedSave->getArrows();

	// loads the current maps rooms
	loadMap();

	SoundManager::stopMusic();
	// Plays the current maps music
	SoundManager::playLoopedMusic(currentMap->mapMusic);
}

void GameplayState::update()
{
	// updates and removes the enemies in the game
	updateEntities();
	removeEntities();
}

void GameplayState::removeEntities()
{
	// checks if the objectRemoval list is not empty
	if (objectToRemove.size() > 0)
	{
		std::vector<GameObject * >::iterator itr = objectList.begin();
		std::vector<int>::iterator IDitr = objectToRemove.begin();

		// checks he ID of the objects in the object list against the ID of the ints in the removal list and deletes them.
		for (IDitr = objectToRemove.begin(); IDitr < objectToRemove.end(); IDitr++)
		{
			for (itr = objectList.begin(); itr < objectList.end(); )
			{
				if ((**itr).ID == *IDitr)
				{
					delete *itr;
					itr = objectList.erase(itr);
				}
				else
				{
					itr++;
				}
			}
		}

		objectToRemove.clear();
	}
}


void GameplayState::updateEntities()
{
	// runs the frames input check
	InputManager::processInputEvents();

	std::vector<GameObject * >::iterator itr = objectList.begin();
	
	// runs the update for all the game objects
	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		(**itr).update();
	}

	// runs the late update for all the game objects
	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		(**itr).lateUpdate();
	}

	// clears the damage colliders
	CollisionManager::clearFrameColliders();
}

void GameplayState::loadMap()
{
	// loads in the current map and adds its rooms to the gameobeject list
	std::vector<Room * >::iterator itr = (*((*currentMap).getRoomList())).begin();
	
	for (itr = (*((*currentMap).getRoomList())).begin(); itr < (*((*currentMap).getRoomList())).end(); itr++)
	{
		// checks if the current room is equal to the rooms ID and then adds that rooms gameObjects to the game
		if ((**itr).groupID == currentRoom)
		{
			addObjectToList(*itr);
			(*itr)->addRoomCollisions();
		}
	}
}

void GameplayState::removeObject(int _index)
{
	// adds a object ID to the remove list so that it can be removed form the game at the end of the frame
	objectToRemove.push_back(_index);
}

void GameplayState::display(SDL_Renderer** _renderer)
{
	// clears the render
	SDL_RenderClear(*_renderer);

	// gets the cameras current offset
	alignCamera();

	std::vector<GameObject * >::iterator itr = objectList.begin();
	
	// calls the draw function for all the object in the game
	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		(**itr).draw(_renderer);
	}

	// draws the render
	SDL_RenderPresent(*_renderer);
}

// Sets the ofset of all the displayed entities
void GameplayState::alignCamera()
{
	int w = 0, h = 0;
	SDL_GetWindowSize((*Camera::window), &w, &h);

	// checks to see if camera is within the bounds of the room based on the x axis
	if ((currentMap->getRoom(currentRoom)->position.x) <= (player->position.x + (player->position.w / 2) - (w / 2)))
	{
		if ((currentMap->getRoom(currentRoom)->position.x + (currentMap->getRoom(currentRoom)->position.w - w) >= (player->position.x + (player->position.w / 2) - (w / 2))))
			Camera::xPositionOfset = -(player->position.x + (player->position.w / 2) - (w / 2));
		else
			Camera::xPositionOfset = -(currentMap->getRoom(currentRoom)->position.x + (currentMap->getRoom(currentRoom)->position.w - w));
	}
	else
		Camera::xPositionOfset = -(currentMap->getRoom(currentRoom)->position.x);

	// checks to see if camera is within the bounds of the room based on the y axis
	if ((currentMap->getRoom(currentRoom)->position.y) <= (player->position.y + (player->position.h / 2) - (h / 2)))
	{
		if ((currentMap->getRoom(currentRoom)->position.y + (currentMap->getRoom(currentRoom)->position.h - h) >= (player->position.y + (player->position.h / 2) - (h / 2))))
			Camera::yPositionOfset = -(player->position.y + (player->position.h / 2) - (h / 2));
		else
			Camera::yPositionOfset = -(currentMap->getRoom(currentRoom)->position.y + (currentMap->getRoom(currentRoom)->position.h - h));
	}
	else
		Camera::yPositionOfset = -(currentMap->getRoom(currentRoom)->position.y);
}

// adds an objec tot the object list in the order of its rendering tag
void GameplayState::addObjectToList(GameObject * _object)
{
	// checks if the object list is greater then 0
	if (objectList.size() > 0)
	{
		std::vector<GameObject * >::iterator itr = objectList.begin();
		bool added = false;

		// iterates throught he list and inputs the new game object one before the rendertag higher then it
		for (itr = objectList.begin(); itr < objectList.end(); itr++)
		{
			if ((*_object).renderTag < (**itr).renderTag)
			{
				itr = objectList.insert(itr, _object);
				added = true;
				itr = objectList.end() - 1;
			}
		}

		// if it hasnt found anything higher then it add it to the end
		if (!added)
		{
			objectList.push_back(_object);
		}
	}
	else
	{
		// adds it to the start if no objects are in the list
		objectList.push_back(_object);
	}
}