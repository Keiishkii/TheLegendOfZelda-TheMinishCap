#include "GameObject.h"

#include <iostream>

#include "GameManager.h"
#include "TextureManager.h"

unsigned int GameObject::ID_Counter = 0;

void GameObject::draw(SDL_Renderer ** _renderer)
{
	if (textureName != "")
	{
		SDL_Rect offsetPosition = position;
		offsetPosition.x += Camera::xPositionOfset;
		offsetPosition.y += Camera::yPositionOfset;

		if (opacity < 255)
		{
			SDL_Texture * blendedTexture(TextureManager::getTexture(textureName));

			SDL_SetTextureBlendMode(blendedTexture, SDL_BLENDMODE_BLEND);

			SDL_SetTextureAlphaMod(blendedTexture, opacity);
			
			SDL_RenderCopy(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &offsetPosition);

			SDL_SetTextureAlphaMod(blendedTexture, 255);
		}
		else
		{
			SDL_RenderCopy(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &offsetPosition);
		}
	}
}