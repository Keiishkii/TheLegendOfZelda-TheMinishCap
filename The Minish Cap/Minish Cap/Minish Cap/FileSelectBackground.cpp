#include "FileSelectBackground.h"

#include "TextureManager.h"

FileSelectBackground::FileSelectBackground(SDL_Rect _pos) : GameObject(_pos)
{
	renderTag = BACKGROUND;
	texturePos = { 2, 668, 240, 160 };
	textureName = "FileSelectScreen";
}

void FileSelectBackground::draw(SDL_Renderer ** _renderer)
{
	switch ((animationFrame / 40) % 4)
	{
	case 0:
		texturePos = { 2, 668, 240, 160 };
		break;
	case 1:
		texturePos = { 243, 668, 240, 160 };
		break;
	case 2:
		texturePos = { 2, 829, 240, 160 };
		break;
	case 3:
		texturePos = { 243, 829, 240, 160 };
		break;
	}

	if (animationFrame >= 159)
	{
		animationFrame = 0;
	}
	else
	{
		animationFrame++;
	}
	
	SDL_RenderCopy(*_renderer, TextureManager::getTexture(textureName), &texturePos, &position);
}