#include "TitleScreenState.h"

#include <iterator>
#include <iostream>

#include "GameManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "InputManager.h"

#include "TitleScreenLightRays.h"
#include "TitleScreenPressAnyButton.h"
#include "TitleScreenSword.h"
#include "TitleScreenFont.h"
#include "FileSelectState.h"

std::vector<GameObject * > TitleScreen::objectList;

void TitleScreen::loadState()
{
	objectList.clear();
	GameManager::gameState = TITLE_SCREEN;


	// Background Image
	addObjectToList(new GameObject(SDL_Rect{0, 0, 480, 320}, SDL_Rect{ 251, 24, 240, 160}, "TitleScreen", TAG_BACKGROUND));
	// Light Effects
	addObjectToList(new TitleScreenLightRays(SDL_Rect{ 0, 0, 480, 320 }));
	// UI
	addObjectToList(new TitleScreenSword(SDL_Rect{ 44, 44, 382, 196 }));
	addObjectToList(new TitleScreenFont(SDL_Rect{ 68, 16, 334, 176 }));
	addObjectToList(new TitleScreenKeyWait(SDL_Rect{ 152, 250, 178, 36 }));


	SoundManager::stopMusic();
	SoundManager::playMusic("01 Title Screen");
}

void TitleScreen::addObjectToList(GameObject * _object)
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

void TitleScreen::update()
{
	std::vector<GameObject * >::iterator itr = objectList.begin();

	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		(**itr).update();
	}

	inputs();
}

void TitleScreen::display(SDL_Renderer** _renderer)
{
	SDL_RenderClear(*_renderer);

	std::vector<GameObject * >::iterator itr = objectList.begin();
			
	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		(**itr).draw(_renderer);
	}

	SDL_RenderPresent(*_renderer);
}

void TitleScreen::inputs()
{
	InputManager::processInputEvents();

	if (InputManager::input.KeyReturnPressed)
	{
		SoundManager::playSound("MC_Menu_Select");
		GameManager::gameState = FILE_SELECT;
		unloadState();
		FileSelect::loadState();
	}
}

void TitleScreen::unloadState()
{
	std::vector<GameObject * >::iterator itr = objectList.begin();

	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		delete	*itr;
	}
	objectList.clear();
}