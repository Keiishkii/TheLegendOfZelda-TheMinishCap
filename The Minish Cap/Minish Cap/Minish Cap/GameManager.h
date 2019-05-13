#ifndef GAME_MANAGER
#define GAME_MANAGER

#include "SaveFile.h"

enum GameState
{
	TITLE_SCREEN,
	FILE_SELECT,
	GAMEPLAY,
	PAUSED
};

class GameManager
{
private:

public:
	static GameState gameState;
	static SaveFile * loadedSave;
	static bool gameRunning;
};

#endif