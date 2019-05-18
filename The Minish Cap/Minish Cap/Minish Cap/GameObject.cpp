#include "GameObject.h"

#include <iostream>

#include "GameManager.h"
#include "TextureManager.h"

unsigned int GameObject::ID_Counter = 0;

// draws the sprite with its current texutre position to the renderer
void GameObject::draw(SDL_Renderer ** _renderer)
{
	if (textureName != "")
	{
		SDL_Rect offsetPosition = position;
		offsetPosition.x += Camera::xPositionOfset;
		offsetPosition.y += Camera::yPositionOfset;

		// checks if opacity is less then fully visable. If so then creating a blend 
		if (opacity < 255)
		{
			// works out the alpha of the texture and draws it to the screen based on the alpha
			SDL_Texture * blendedTexture(TextureManager::getTexture(textureName));

			SDL_SetTextureBlendMode(blendedTexture, SDL_BLENDMODE_BLEND);

			SDL_SetTextureAlphaMod(blendedTexture, opacity);
			
			SDL_RenderCopy(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &offsetPosition);

			SDL_SetTextureAlphaMod(blendedTexture, 255);
		}
		else
		{	
			//draws to the screen
			SDL_RenderCopy(*_renderer, (TextureManager::getTexture(textureName)), &texturePos, &offsetPosition);
		}
	}
}