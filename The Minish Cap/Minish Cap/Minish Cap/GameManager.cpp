#include "GameManager.h"

// the current scene that the game is running
GameState GameManager::gameState = TITLE_SCREEN;
// The currnet save loaded in the game
SaveFile * GameManager::loadedSave = nullptr;
// The status on whether the game is currently running or if its been closed
bool GameManager::gameRunning = true;