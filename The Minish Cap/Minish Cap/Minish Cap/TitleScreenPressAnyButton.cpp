#include "TitleScreenPressAnyButton.h"

#include "TextureManager.h"

TitleScreenKeyWait::TitleScreenKeyWait(SDL_Rect _pos) : GameObject(_pos)
{
	opacity = 0;
	renderTag = TAG_UI;
	texturePos = { 327, 188, 89, 18};
	textureName = "TitleScreen";
}

void TitleScreenKeyWait::draw(SDL_Renderer ** _renderer)
{
	if (animationFrame >= 200)
	{
		if ((((animationFrame - 200) / 30) % 2) == 0)
		{
			opacity = 255;
		}
		else
		{
			opacity = 0;
		}
		
		if (animationFrame >= 260)
		{
			animationFrame = 200;
		}
		else
		{
			animationFrame++;
		}
	}
	else
	{
	animationFrame++;
	}

	SDL_Texture * blendedTexture(TextureManager::getTexture(textureName));

	SDL_SetTextureBlendMode(blendedTexture, SDL_BLENDMODE_BLEND);

	SDL_SetTextureAlphaMod(blendedTexture, opacity);

	SDL_RenderCopy(*_renderer, blendedTexture, &texturePos, &position);

	SDL_SetTextureAlphaMod(blendedTexture, 255);
}