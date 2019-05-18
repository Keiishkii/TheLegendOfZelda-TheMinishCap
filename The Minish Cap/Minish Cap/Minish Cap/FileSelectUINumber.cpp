#include "FileSelectUINumber.h"

#include "TextureManager.h"
#include "FileSelectState.h"

FileSelectUINumber::FileSelectUINumber(SDL_Rect _pos, int _fileID) : GameObject(_pos)
{
	renderTag = TAG_UI;
	fileID = _fileID;
	texturePos = { 2, 62, 69, 26 };
	textureName = "FileSelectScreen";
}

// draws the sprite with its current texutre position to the renderer
void FileSelectUINumber::draw(SDL_Renderer ** _renderer)
{
	switch (fileID)
	{
		case 0:
		{
			if (FileSelect::selectedSave != fileID)
			{
				texturePos = { 124, 120, 8, 8 };
			}
			else
			{
				texturePos = { 154, 120, 8, 8 };
			}
			break;
		}
		case 1:
		{
			if (FileSelect::selectedSave != fileID)
			{
				texturePos = { 132, 120, 8, 8 };
			}
			else
			{
				texturePos = { 162, 120, 8, 8 };
			}
			break;
		}
		case 2:
		{
			if (FileSelect::selectedSave != fileID)
			{
				texturePos = { 142, 120, 8, 8 };
			}
			else
			{
				texturePos = { 172, 120, 8, 8 };
			}
			break;
		}
	}

	SDL_RenderCopy(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &position);
}