#include "FileSelectUI.h"

#include "TextureManager.h"
#include "FileSelectState.h"

FileSelectUI::FileSelectUI(SDL_Rect _pos, int _fileID) : GameObject(_pos)
{
	renderTag = TAG_UI;
	fileID = _fileID;
	texturePos = { 2, 62, 69, 26 };
	textureName = "FileSelectScreen";
}

void FileSelectUI::draw(SDL_Renderer ** _renderer)
{
	if (FileSelect::selectedSave == fileID)
	{
		texturePos = { 2, 62, 69, 26 };
	}
	else
	{
		texturePos = { 2, 32, 69, 26 };
	}

	SDL_RenderCopy(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &position);
}