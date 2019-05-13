#include "GameManager.h"

GameState GameManager::gameState = TITLE_SCREEN;
SaveFile * GameManager::loadedSave = nullptr;

bool GameManager::gameRunning = true;