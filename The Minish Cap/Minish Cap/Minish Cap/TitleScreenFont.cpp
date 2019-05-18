#include "TitleScreenFont.h"

#include "TextureManager.h"
#include "SoundManager.h"

TitleScreenFont::TitleScreenFont(SDL_Rect _pos) : GameObject(_pos)
{
	opacity = 0;
	renderTag = TAG_UI;
	texturePos = { 285, 447, 167, 88};
	textureName = "TitleScreen";
}

// draws the sprite with its current texutre position to the renderer
void TitleScreenFont::draw(SDL_Renderer ** _renderer)
{
	if (animationFrame >= 180 && opacity != 255)
	{
		opacity = 255;
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

void TitleScreenFont::update()
{
	if (animationFrame >= 180 && !triggerSoundPlayed)
	{
		triggerSoundPlayed = true;
		SoundManager::playSound("MC_Emote_Exclaim");
	}
}