#include "TextureManager.h"

#include <iostream>

std::map<std::string, SDL_Texture * > TextureManager::spriteMapList;

bool TextureManager::loadTexture(std::string _path, std::string _name, SDL_Renderer ** _renderer)
{
	const char * pathPtr = _path.c_str();
	bool foundFile = false;

	SDL_Surface* surface = SDL_LoadBMP(pathPtr);

	if (surface != NULL)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(*_renderer, surface);
		SDL_FreeSurface(surface);
		
		spriteMapList[_name] = texture;
		foundFile = true;
	}
	else
	{
		std::cout << SDL_GetError() << std::endl;
	}

	return foundFile;
}

SDL_Texture * TextureManager::getTexture(std::string _name)
{
	return spriteMapList[_name];
}

bool TextureManager::loadAllTextures(SDL_Renderer ** _renderer)
{
	bool texturesLoaded = false;

	texturesLoaded =
	(
		//UI
		loadTexture("Textures/TitleScreenSpriteSheet.bmp", "TitleScreen", _renderer) &&
		loadTexture("Textures/FileSelectScreenSpriteSheet.bmp", "FileSelectScreen", _renderer) &&
		//Maps
		loadTexture("Textures/RoyalCryptSpriteSheet.bmp", "RoyalCrypt", _renderer) &&
		// Entities
		loadTexture("Textures/LinkSpriteSheet.bmp", "Link", _renderer)
	);

	return texturesLoaded;
}