#include "StateManager.h"

#include <iostream>

#include "GameManager.h"

#include "TitleScreenState.h"
#include "FileSelectState.h"
#include "GameplayState.h"

void StateManager::update(SDL_Window** _window, SDL_Renderer** _renderer)
{
	switch (GameManager::gameState)
	{
	case TITLE_SCREEN:
		TitleScreen::update();
		TitleScreen::display(_renderer);
		break;
	case FILE_SELECT:
		FileSelect::update();
		FileSelect::display(_renderer);
		break;
	case GAMEPLAY:
		GameplayState::update();
		GameplayState::display(_renderer);
		break;
	}
}