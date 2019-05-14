#include "TitleScreenLightRays.h"

#include <SDL.h>
#include <iostream>

#include "TextureManager.h"

TitleScreenLightRays::TitleScreenLightRays(SDL_Rect _pos) : GameObject(_pos)
{
	renderTag = TAG_BACKGROUND_PARTICLES;
	texturePos = {6, 24, 240, 160};
	textureName = "TitleScreen";
}

void TitleScreenLightRays::draw(SDL_Renderer ** _renderer)
{
	switch ((animationFrame / 10) % 4)
	{
	case 0:
		texturePos = { 6, 24, 240, 160 };
		break;
	case 1:
		texturePos = { 6, 187, 240, 160 };
		break;
	case 2:
		texturePos = { 6, 350, 240, 160 };
		break;
	case 3:
		texturePos = { 6, 513, 240, 160 };
		break;
	}

	if (animationFrame >= 39)
	{
		animationFrame = 0;
	}
	else
	{
		animationFrame++;
	}

	SDL_Texture * blendedTexture (TextureManager::getTexture(textureName));

	SDL_SetTextureBlendMode(blendedTexture, SDL_BLENDMODE_BLEND);

	if ((animationFrame % 10) == 0)
	{
		opacity = (100 + (rand() % 50));
	}

	SDL_SetTextureAlphaMod(blendedTexture, opacity);

	SDL_RenderCopy(*_renderer, blendedTexture, &texturePos, &position);

	SDL_SetTextureAlphaMod(blendedTexture, 255);
}