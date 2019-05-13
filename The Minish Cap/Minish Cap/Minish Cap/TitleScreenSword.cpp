#include "TitleScreenSword.h"

#include "TextureManager.h"

TitleScreenSword::TitleScreenSword(SDL_Rect _pos) : GameObject(_pos)
{
	opacity = 255;
	renderTag = UI;
	texturePos = { 273, 236, 191, 98};
	textureName = "TitleScreen";
}

void TitleScreenSword::draw(SDL_Renderer ** _renderer)
{
	if (animationFrame < 100)
	{
		animationFrame++;

		int frameDif = (100 - animationFrame) * 12;
		
		float aspectMultiplier = 382.0f / 196.0f;

		position = { (44 - (int)((float) frameDif * aspectMultiplier)), (54 - (frameDif)), (382 + (int)((float) frameDif * 2.0f * aspectMultiplier)), (196 + (frameDif * 2)) };
	}
	
	SDL_RenderCopy(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &position);
}