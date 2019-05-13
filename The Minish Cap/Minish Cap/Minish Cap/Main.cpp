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

int main(int argc, char * argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	if (initialistion(&window, &renderer))
	{
		TitleScreen::loadState();
		gameLoop(&window, &renderer);
	}

	return 0;
}

void gameLoop(SDL_Window** window, SDL_Renderer** renderer)
{	

	clock_t start = clock();
	clock_t end = clock();

	while (GameManager::gameRunning)
	{
		start = clock();

		StateManager::update(window, renderer);

		end = clock();

		int sleepDuration = (1000 / 60) - (((end - start) / (double) CLOCKS_PER_SEC) * 1000);

		if (sleepDuration > 0)
		{
			Sleep(sleepDuration);
		}
	}
}

bool initialistion (SDL_Window** _window, SDL_Renderer** _renderer)
{
	std::srand(time(NULL));

	bool init = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to initialise - " << SDL_GetError() << std::endl;
		init = false;
	}
	else
	{
		*_window = SDL_CreateWindow("The Legend of Zelda: The Minish Cap", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 320, SDL_WINDOW_SHOWN);
		if (*_window == NULL)
		{
			std::cout << "Failed to create window - " << SDL_GetError() << std::endl;
			init = false;
		}
		else
		{
			Camera::window = _window;
			*_renderer = SDL_CreateRenderer(*_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (*_renderer == NULL)
			{
				std::cout << "Failed to create renderer -: " << SDL_GetError() << std::endl;
				init = false;
			}
			else
			{
				if (!TextureManager::loadAllTextures(_renderer))
				{
					std::cout << "Failed to load textures -: " << SDL_GetError() << std::endl;
					init = false;
				}
				else
				{

					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
					{
						std::cout << "Failed to initialse mixer -: " << SDL_GetError() << std::endl;
						init = false;
					}
					else
					{
						if (!SoundManager::loadAllAudio())
						{
							std::cout << "Failed to load sounds -: " << SDL_GetError() << std::endl;
							init = false;
						}
						else
						{
							MapManager::loadAllMaps();
							SaveFileManager::loadSaves();
						}
					}
				}
			}
		}
	}

	return init;
}