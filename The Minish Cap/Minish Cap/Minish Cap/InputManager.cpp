#include "InputManager.h"

#include "GameManager.h"

#include "SDL.h"

// struct for storing all player inputs
InputManager::inputEvents InputManager::input = { false };

// Checks the frames input
void InputManager::processInputEvents()
{
	// variables to store prevous frames input
	InputManager::inputEvents prevousInput;

	// sets prevous frames input
	prevousInput = input;

	// sets current frames input to false
	input = { false };

	// sets current frames down values to the prevous frames
	input.KeyWDown = prevousInput.KeyWDown;
	input.KeySDown = prevousInput.KeySDown;
	input.KeyDDown = prevousInput.KeyDDown;
	input.KeyADown = prevousInput.KeyADown;

	input.KeyUpDown = prevousInput.KeyUpDown;
	input.KeyDownDown = prevousInput.KeyDownDown;
	input.KeyLeftDown = prevousInput.KeyLeftDown;
	input.KeyRightDown = prevousInput.KeyRightDown;

	input.KeyReturnDown = prevousInput.KeyReturnDown;

	input.MouseLeftDown = prevousInput.MouseLeftDown;
	input.MouseRightDown = prevousInput.MouseRightDown;

	SDL_Event e;
	
	// Polls events while there are events active
	while (SDL_PollEvent(&e))
	{
		// 
		switch ( e.type)
		{
			case SDL_KEYDOWN:
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_w:
					{
						if (!prevousInput.KeyWDown)
						{
							input.KeyWPressed = true;
							input.KeyWDown = true;
						}
						break;
					}
					case SDLK_s:
					{
						if (!prevousInput.KeySDown)
						{
							input.KeySPressed = true;
							input.KeySDown = true;
						}
						break;
					}
					case SDLK_a:
					{
						if (!prevousInput.KeyADown)
						{
							input.KeyAPressed = true;
							input.KeyADown = true;
						}
						break;
					}
					case SDLK_d:
					{
						if (!prevousInput.KeyDDown)
						{
							input.KeyDPressed = true;
							input.KeyDDown = true;
						}
						break;
					}
					case SDLK_UP:
					{
						if (!prevousInput.KeyUpDown)
						{
							input.KeyUpPressed = true;
							input.KeyUpDown = true;
						}
						break;
					}
					case SDLK_DOWN:
					{
						if (!prevousInput.KeyDownDown)
						{
							input.KeyDownPressed = true;
							input.KeyDownDown = true;
						}
						break;
					}
					case SDLK_LEFT:
					{
						if (!prevousInput.KeyLeftDown)
						{
							input.KeyLeftPressed = true;
							input.KeyLeftDown = true;
						}
						break;
					}
					case SDLK_RIGHT:
					{
						if (!prevousInput.KeyRightDown)
						{
							input.KeyRightPressed = true;
							input.KeyRightDown = true;
						}
						break;
					}
					case SDLK_RETURN:
					{
						if (!prevousInput.KeyReturnDown)
						{
							input.KeyReturnPressed = true;
							input.KeyReturnDown = true;
						}
						break;
					}
					case SDLK_SPACE:
					{
						if (!prevousInput.KeySpaceDown)
						{
							input.KeySpacePressed = true;
							input.KeySpaceDown = true;
						}
						break;
					}
				}
				break;
			}
			case SDL_KEYUP:
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_w:
					{
						if (prevousInput.KeyWDown)
						{
							input.KeyWRelease = true;
							input.KeyWDown = false;
						}
						break;
					}
					case SDLK_s:
					{
						if (prevousInput.KeySDown)
						{
							input.KeySRelease = true;
							input.KeySDown = false;
						}
						break;
					}
					case SDLK_a:
					{
						if (prevousInput.KeyADown)
						{
							input.KeyARelease = true;
							input.KeyADown = false;
						}
						break;
					}
					case SDLK_d:
					{
						if (prevousInput.KeyDDown)
						{
							input.KeyDRelease = true;
							input.KeyDDown = false;
						}
						break;
					}
					case SDLK_UP:
					{
						if (prevousInput.KeyUpDown)
						{
							input.KeyUpRelease = true;
							input.KeyUpDown = false;
						}
						break;
					}
					case SDLK_DOWN:
					{
						if (prevousInput.KeyDownDown)
						{
							input.KeyDownRelease = true;
							input.KeyDownDown = false;
						}
						break;
					}
					case SDLK_LEFT:
					{
						if (prevousInput.KeyLeftDown)
						{
							input.KeyLeftRelease = true;
							input.KeyLeftDown = false;
						}
						break;
					}
					case SDLK_RIGHT:
					{
						if (prevousInput.KeyRightDown)
						{
							input.KeyRightRelease = true;
							input.KeyRightDown = false;
						}
						break;
					}
					case SDLK_RETURN:
					{
						if (prevousInput.KeyReturnDown)
						{
							input.KeyReturnRelease = true;
							input.KeyReturnDown = false;
						}
						break;
					}
					case SDLK_SPACE:
					{
						if (prevousInput.KeySpaceDown)
						{
							input.KeySpaceRelease = true;
							input.KeySpaceDown = false;
						}
						break;
					}
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				switch (e.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						if (!prevousInput.MouseLeftDown)
						{
							input.MouseLeftClicked = true;
							input.MouseLeftDown = false;
						}
						break;
					}
					case SDL_BUTTON_RIGHT:
					{
						if (!prevousInput.MouseRightDown)
						{
							input.MouseRightClicked = true;
							input.MouseRightDown = false;
						}
						break;
					}
				}
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				switch (e.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						if (prevousInput.MouseLeftDown)
						{
							input.MouseLeftRelease = true;
							input.MouseLeftDown = false;
						}
						break;
					}
					case SDL_BUTTON_RIGHT:
					{
						if (prevousInput.MouseRightDown)
						{
							input.MouseRightRelease = true;
							input.MouseRightDown = false;
						}
						break;
					}
				}
				break;
			}
			case SDL_QUIT:
			{
				GameManager::gameRunning = false;
				break;
			}
		}
	}
}