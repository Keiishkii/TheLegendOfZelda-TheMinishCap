#include "FileSelectCursor.h"

#include "TextureManager.h"
#include "FileSelectState.h"

FileSelectCursor::FileSelectCursor(SDL_Rect _pos) : GameObject(_pos)
{
	animationFrame = 0;
	renderTag = TAG_UI;
	texturePos = { 2, 62, 69, 26 };
	textureName = "FileSelectScreen";
}

void FileSelectCursor::update()
{
	switch (FileSelect::selectedSave)
	{
	case 0:
		position = {34, 65, 34, 34};
		break;
	case 1:
		position = { 34, 129, 34, 34 };
		break;
	case 2:
		position = { 34, 193, 34, 34 };
		break;
	}
}

// draws the sprite with its current texutre position to the renderer
void FileSelectCursor::draw(SDL_Renderer ** _renderer)
{
	if (animationFrame < 8)
	{
		texturePos = { 2, 116, 16, 16 };
	}
	else if (animationFrame < 16)
	{
		texturePos = { 19, 116, 16, 16 };
	}
	else if (animationFrame < 24)
	{
		texturePos = { 36, 116, 16, 16 };
	}
	else if (animationFrame < 32)
	{
		texturePos = { 53, 116, 16, 16 };
	}
	else if (animationFrame < 40)
	{
		texturePos = { 70, 116, 16, 16 };
	}
	else if (animationFrame < 48)
	{
		texturePos = { 87, 116, 16, 16 };
	}
	else if (animationFrame < 56)
	{
		texturePos = { 104, 116, 16, 16 };
	}

	if (animationFrame >= 56)
	{
		animationFrame = 0;
	}
	else
	{
		animationFrame++;
	}

	SDL_RenderCopy(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &position);
}