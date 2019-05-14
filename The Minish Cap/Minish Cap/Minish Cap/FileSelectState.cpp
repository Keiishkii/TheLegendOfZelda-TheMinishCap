#include "FileSelectState.h"

#include <iostream>

#include "InputManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "SaveFileManager.h"
#include "GameplayState.h"

#include "SaveFile.h"

#include "FileSelectBackground.h"
#include "FileSelectCursor.h"
#include "FileSelectUI.h"
#include "FileSelectUINumber.h"

int FileSelect::selectedSave = 0;

std::vector<GameObject * > FileSelect::objectList;

void FileSelect::loadState()
{
	objectList.clear();
	GameManager::gameState = FILE_SELECT;


	// Background Image
	addObjectToList(new FileSelectBackground(SDL_Rect{ 0, 0, 480, 320 }));
	// UI
	addObjectToList(new GameObject(SDL_Rect{ 10, 0, 324, 46 }, SDL_Rect{ 1, 2, 162, 23 }, "FileSelectScreen", TAG_UI));

	addObjectToList(new FileSelectUI(SDL_Rect{ 60, 56, 138, 52 }, 0));
	addObjectToList(new FileSelectUI(SDL_Rect{ 60, 120, 138, 52 }, 1));
	addObjectToList(new FileSelectUI(SDL_Rect{ 60, 184, 138, 52 }, 2));

	addObjectToList(new FileSelectCursor(SDL_Rect{ 34, 64, 34, 34 }));

	addObjectToList(new FileSelectUINumber(SDL_Rect{ 42, 74, 16, 16 }, 0));
	addObjectToList(new FileSelectUINumber(SDL_Rect{ 42, 138, 16, 16 }, 1));
	addObjectToList(new FileSelectUINumber(SDL_Rect{ 42, 202, 16, 16 }, 2));

	addObjectToList(new GameObject(SDL_Rect{ 214, 68, 216, 152 }, SDL_Rect{ 81, 32, 108, 76 }, "FileSelectScreen", TAG_UI, 0, 100));

	displayFileContent();

	SoundManager::stopMusic();
	SoundManager::playLoopedMusic("02 File Select");
}

void FileSelect::unloadState()
{
	std::vector<GameObject * >::iterator itr = objectList.begin();

	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		delete	*itr;
	}
	objectList.clear();
}

void FileSelect::update()
{
	std::vector<GameObject * >::iterator itr = objectList.begin();

	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		(**itr).update();
	}

	inputs();
}

void FileSelect::display(SDL_Renderer ** _renderer)
{
	SDL_RenderClear(*_renderer);

	std::vector<GameObject * >::iterator itr = objectList.begin();

	for (itr = objectList.begin(); itr < objectList.end(); itr++)
	{
		(**itr).draw(_renderer);
	}

	SDL_RenderPresent(*_renderer);
}

void FileSelect::inputs()
{
	InputManager::processInputEvents();

	if (InputManager::input.KeyWPressed || InputManager::input.KeyUpPressed)
		moveUpSelected();

	if (InputManager::input.KeySPressed || InputManager::input.KeyDownPressed)
		moveDownSelected();

	if (InputManager::input.KeyReturnPressed)
		loadSelectedFile();
}

void FileSelect::addObjectToList(GameObject * _object)
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

void FileSelect::moveUpSelected()
{
	if (selectedSave > 0)
	{
		SoundManager::playSound("MC_Menu_Cursor");
		selectedSave--;
		displayFileContent();
	}
}

void FileSelect::moveDownSelected()
{
	if (selectedSave < 2)
	{
		SoundManager::playSound("MC_Menu_Cursor");
		selectedSave++;
		displayFileContent();
	}
}

void FileSelect::loadSelectedFile()
{
	SoundManager::playSound("MC_Menu_Select");
	unloadState();
	GameManager::gameState = GAMEPLAY;
	GameManager::loadedSave = SaveFileManager::getSave(selectedSave);
	GameplayState::loadState();
}

void FileSelect::displayFileContent()
{
	removeFileDisplay();

	SaveFile * selectedFile = SaveFileManager::getSave(selectedSave);

	int maxHearts = (*selectedFile).getMaxHealth();
	int currentHearts = (*selectedFile).getCurrentHealth();

	for (int i = 0; i < ((maxHearts / 4)); i++)
	{
		int heartTexture = (currentHearts - (4 * i));

		if (heartTexture >= 4)
		{
			addObjectToList(new GameObject(SDL_Rect{ 242 + (i * 16) + ((((i) / 10) % 2) * -160), 162 + ((((i) / 10) % 2) * 16), 18, 16 }, SDL_Rect{ 2, 156, 9, 8 }, "FileSelectScreen", TAG_UI, 1));
		}
		else if (heartTexture == 3)
		{
			addObjectToList(new GameObject(SDL_Rect{ 242 + (i * 16) + ((((i) / 10) % 2) * -160), 162 + ((((i) / 10) % 2) * 16), 18, 16 }, SDL_Rect{ 13, 156, 9, 8 }, "FileSelectScreen", TAG_UI, 1));
		}
		else if (heartTexture == 2)
		{
			addObjectToList(new GameObject(SDL_Rect{ 242 + (i * 16) + ((((i) / 10) % 2) * -160), 162 + ((((i) / 10) % 2) * 16), 18, 16 }, SDL_Rect{ 24, 156, 9, 8 }, "FileSelectScreen", TAG_UI, 1));
		}
		else if (heartTexture == 1)
		{
			addObjectToList(new GameObject(SDL_Rect{ 242 + (i * 16) + ((((i) / 10) % 2) * -160), 162 + ((((i) / 10) % 2) * 16), 18, 16 }, SDL_Rect{ 35, 156, 9, 8 }, "FileSelectScreen", TAG_UI, 1));
		}
		else if (heartTexture <= 0)
		{
			addObjectToList(new GameObject(SDL_Rect{ 242 + (i * 16) + ((((i) / 10) % 2) * -160), 162 + ((((i) / 10) % 2) * 16), 18, 16 }, SDL_Rect{ 46, 156, 9, 8 }, "FileSelectScreen", TAG_UI, 1));
		}
	}
}

void FileSelect::removeFileDisplay()
{
	std::vector<GameObject * >::iterator itr = objectList.begin();
	
	int removeNum = 0;

	for (itr = objectList.begin(); itr < objectList.end(); )
	{
		if ((**itr).groupID == 1)
		{
			delete *itr;
			itr = objectList.erase(itr);
			removeNum++;
		}
		else
		{
			itr++;
		}
	}
}