#include "StateManager.h"

#include <iostream>

#include "GameManager.h"

#include "TitleScreenState.h"
#include "FileSelectState.h"
#include "GameplayState.h"

// runs the update and display functions depending on what scene is currently being renderered.
void StateManager::update(SDL_Window** _window, SDL_Renderer** _renderer)
{
	// Checks what scene is currently open
	switch (GameManager::gameState)
	{
		// TitleScreen for when the game loads up
	case TITLE_SCREEN:
		TitleScreen::update();
		TitleScreen::display(_renderer);
		break;
		// FileSelect for when selecting a save file
	case FILE_SELECT:
		FileSelect::update();
		FileSelect::display(_renderer);
		break;
		// Gameplay for when actually playing the game with the player character
	case GAMEPLAY:
		GameplayState::update();
		GameplayState::display(_renderer);
		break;
	}
}