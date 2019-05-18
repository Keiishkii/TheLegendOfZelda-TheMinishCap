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

// adds an objec tot the object list in the order of its rendering tag
void TitleScreen::addObjectToList(GameObject * _object)
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

// update function for the title screen
void TitleScreen::update()
{
	std::vector<GameObject * >::iterator itr = objectList.begin();

	// calls the update function for all objects in the object list
	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		(**itr).update();
	}

	// processes the inputs given by the player
	inputs();
}

// display function for the title screen
void TitleScreen::display(SDL_Renderer** _renderer)
{
	SDL_RenderClear(*_renderer);

	std::vector<GameObject * >::iterator itr = objectList.begin();
			
	// calls the display function for all of the objects
	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		(**itr).draw(_renderer);
	}

	SDL_RenderPresent(*_renderer);
}

// player input functions
void TitleScreen::inputs()
{
	InputManager::processInputEvents();

	// if enter is pressed the title screen closes and the file select opens
	if (InputManager::input.KeyReturnPressed)
	{
		SoundManager::playSound("MC_Menu_Select");
		GameManager::gameState = FILE_SELECT;
		unloadState();
		FileSelect::loadState();
	}
}

// unloads all the new objects in the lists when the list is closing
void TitleScreen::unloadState()
{
	std::vector<GameObject * >::iterator itr = objectList.begin();

	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		delete	*itr;
	}
	objectList.clear();
}