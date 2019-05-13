#include "GameplayState.h"

#include <iostream>

#include "SoundManager.h"
#include "GameManager.h"
#include "MapManager.h"
#include "InputManager.h"

#include "Camera.h"

std::vector<GameObject * > GameplayState::objectList;

Map * GameplayState::currentMap = nullptr;

Player * GameplayState::player = nullptr;

int GameplayState::currentRoom = 0;
int GameplayState::prevousRoom = 0;

void GameplayState::loadState()
{
	objectList.clear();
	GameManager::gameState = GAMEPLAY;

	if (currentMap == nullptr)
	{
		if (GameManager::loadedSave != nullptr)
		{
			currentMap = MapManager::getMap((*GameManager::loadedSave).map);
			prevousRoom = (*MapManager::getMap((*GameManager::loadedSave).map)).defaultRoom;
			currentRoom = (*MapManager::getMap((*GameManager::loadedSave).map)).defaultRoom;
		}
	}

	if (player == nullptr)
	{
		player = new Player(SDL_Rect{currentMap->defaultX, currentMap->defaultY, 64, 64});
	}
	
	addObjectToList(player);

	loadMap();

	SoundManager::stopMusic();
	SoundManager::playLoopedMusic(currentMap->mapMusic);
}

void GameplayState::update()
{
	updateEntities();
}

void GameplayState::updateEntities()
{
	std::vector<GameObject * >::iterator itr = objectList.begin();

	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		(**itr).update();
	}

	InputManager::processInputEvents();
}

void GameplayState::loadMap()
{
	std::vector<Room * >::iterator itr = (*((*currentMap).getRoomList())).begin();
	
	

	for (itr = (*((*currentMap).getRoomList())).begin(); itr < (*((*currentMap).getRoomList())).end(); itr++)
	{
		if ((**itr).groupID == currentRoom)
		{
			addObjectToList(*itr);
			(*itr)->addRoomCollisions();
		}
	}
}

void GameplayState::display(SDL_Renderer** _renderer)
{
	SDL_RenderClear(*_renderer);

	alignCamera();

	std::vector<GameObject * >::iterator itr = objectList.begin();
	
	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		(**itr).draw(_renderer);
	}

	SDL_RenderPresent(*_renderer);
}

void GameplayState::alignCamera()
{
	int w, h;
	SDL_GetWindowSize((*Camera::window), &w, &h);
	
	if ((currentMap->getRoom(currentRoom)->position.x) <= (player->position.x + (player->position.w / 2) - (w / 2)))
	{
		if ((currentMap->getRoom(currentRoom)->position.x + (currentMap->getRoom(currentRoom)->position.w - w) >= (player->position.x + (player->position.w / 2) - (w / 2))))
			Camera::xPositionOfset = -(player->position.x + (player->position.w / 2) - (w / 2));
		else
			Camera::xPositionOfset = -(currentMap->getRoom(currentRoom)->position.x + (currentMap->getRoom(currentRoom)->position.w - w));
	}
	else
		Camera::xPositionOfset = -(currentMap->getRoom(currentRoom)->position.x);


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

void GameplayState::addObjectToList(GameObject * _object)
{
	if (objectList.size() > 0)
	{
		std::vector<GameObject * >::iterator itr = objectList.begin();
		bool added = false;

		for (itr = objectList.begin(); itr < objectList.end(); itr++)
		{
			if ((*_object).renderTag < (**itr).renderTag)
			{
				itr = objectList.insert(itr, _object);
				added = true;
				itr = objectList.end() - 1;
			}
		}

		if (!added)
		{
			objectList.push_back(_object);
		}
	}
	else
	{
		objectList.push_back(_object);
	}
}