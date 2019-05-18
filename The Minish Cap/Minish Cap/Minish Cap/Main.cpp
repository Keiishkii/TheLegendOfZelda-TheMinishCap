#include <iostream>
#include <SDL.h>
#include <ctime>
#include <time.h>
#include <windows.h>

#include "GameManager.h"
#include "TextureManager.h"
#include "MapManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "SaveFileManager.h"

#include "TitleScreenState.h"

bool initialistion(SDL_Window** window, SDL_Renderer** renderer);
void gameLoop(SDL_Window** window, SDL_Renderer** renderer);
void programExit();

// Program entrance
int main(int argc, char * argv[])
{
	// Debug code for checking for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	// initialises the window and renderer
	SDL_Window* window;
	SDL_Renderer* renderer;

	//Loads in game data and starts the game loop if initialisation failes program will exit
	if (initialistion(&window, &renderer))
	{
		// Runs the load state for the titlescreen
		TitleScreen::loadState();
		// Enters the game loop
		gameLoop(&window, &renderer);
	}
	
	// Unloads varaibles from memory
	programExit();
	
	// program exit
	return 0;
}

//Unloads all variables within the program from memory
void programExit()
{
	// Unloads all SDL related news
	SDL_Quit();

	//TextureManager::unloadAllTextures();
	//SoundManager::unloadAllAudio();
	//MapManager::unloadAllMaps();
	//delete GameManager::loadedSave;

}

// main game loop
void gameLoop(SDL_Window** window, SDL_Renderer** renderer)
{	
	// create clock variables to track frame times
	clock_t start = clock();
	clock_t end = clock();

	// while the game is running repeats
	while (GameManager::gameRunning)
	{
		// sets clock at start of frame
		start = clock();

		// one frame of the games run time
		StateManager::update(window, renderer);

		// sets clock at end of frame
		end = clock();

		// calculates how long the system needs to sleep so that the frames are equal.
		int sleepDuration = (1000 / 60) - (((end - start) / (double) CLOCKS_PER_SEC) * 1000);

		// if the time is greater the 0 sleep for that long
		if (sleepDuration > 0)
		{
			Sleep(sleepDuration);
		}
	}
}

//loads in all assest and intialises window
bool initialistion (SDL_Window** _window, SDL_Renderer** _renderer)
{
	// Seeds the random number generator based on the systems current time
	std::srand(time(NULL));

	// trigger to see if the program succeceds in loading
	bool init = true;

	// Initialises everything to do with SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to initialise - " << SDL_GetError() << std::endl;
		init = false;
	}
	else
	{
		// creates the window
		*_window = SDL_CreateWindow("The Legend of Zelda: The Minish Cap", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 320, SDL_WINDOW_SHOWN);
		if (*_window == NULL)
		{
			std::cout << "Failed to create window - " << SDL_GetError() << std::endl;
			init = false;
		}
		else
		{
			Camera::window = _window;
			// Creates the renderer
			*_renderer = SDL_CreateRenderer(*_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (*_renderer == NULL)
			{
				std::cout << "Failed to create renderer -: " << SDL_GetError() << std::endl;
				init = false;
			}
			else
			{
				//Loads in all the texture files to memeory
				if (!TextureManager::loadAllTextures(_renderer))
				{
					std::cout << "Failed to load textures -: " << SDL_GetError() << std::endl;
					init = false;
				}
				else
				{
					// initialises the audio mixer
					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
					{
						std::cout << "Failed to initialse mixer -: " << SDL_GetError() << std::endl;
						init = false;
					}
					else
					{
						//Loads in all the audio files to memory
						if (!SoundManager::loadAllAudio())
						{
							std::cout << "Failed to load sounds -: " << SDL_GetError() << std::endl;
							init = false;
						}
						else
						{
							// loads in the map files
							MapManager::loadAllMaps();
							// loads in the sound files
							SaveFileManager::loadSaves();
						}
					}
				}
			}
		}
	}

	// returns the success of the the initialisation
	return init;
}