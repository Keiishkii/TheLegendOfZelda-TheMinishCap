#include "TextureManager.h"

#include <iostream>

// list of all texture maps in the game
std::map<std::string, SDL_Texture * > TextureManager::spriteMapList;

// loads in a texture given a name and a path
bool TextureManager::loadTexture(std::string _path, std::string _name, SDL_Renderer ** _renderer)
{
	// converts the string to a usable char array
	const char * pathPtr = _path.c_str();
	bool foundFile = false;

	// creates a surface of the spritemap
	SDL_Surface* surface = SDL_LoadBMP(pathPtr);

	// checks to see if the surface succeseded in creating
	if (surface != NULL)
	{
		// turns the surface into a texture
		SDL_Texture* texture = SDL_CreateTextureFromSurface(*_renderer, surface);
		SDL_FreeSurface(surface);
		
		// adds the texture to the spritemap list
		spriteMapList[_name] = texture;
		foundFile = true;
	}
	else
	{
		std::cout << SDL_GetError() << std::endl;
	}

	// returns wether the surface was ever made
	return foundFile;
}

// takes in the name of a spritemap and returns it from the map
SDL_Texture * TextureManager::getTexture(std::string _name)
{
	return spriteMapList[_name];
}

// loads in every texture for the game
bool TextureManager::loadAllTextures(SDL_Renderer ** _renderer)
{
	bool texturesLoaded = false;

	// Check to see if all textures are loaded succsessfully
	texturesLoaded =
	(
		//UI
		loadTexture("Textures/TitleScreenSpriteSheet.bmp", "TitleScreen", _renderer) &&
		loadTexture("Textures/FileSelectScreenSpriteSheet.bmp", "FileSelectScreen", _renderer) &&
		//Maps
		loadTexture("Textures/RoyalCryptSpriteSheet.bmp", "RoyalCrypt", _renderer) &&
		// Entities
		loadTexture("Textures/Rupees.bmp", "Rupees", _renderer) &&
		loadTexture("Textures/Pot.bmp", "Pot", _renderer) &&
		loadTexture("Textures/LinkSpriteSheet.bmp", "Link", _renderer)
	);

	// returns false if one of the textures failed to load
	return texturesLoaded;
}

// unlaods the textures
void TextureManager::unloadAllTextures()
{
	std::map<std::string, SDL_Texture * >::iterator itr = spriteMapList.begin();
	// deletes the textures in the spriteList and emptys the list
	for (itr = spriteMapList.begin(); itr != spriteMapList.end(); itr++)
	{
		delete itr->second;
	}

	// clears the list
	spriteMapList.clear();
}