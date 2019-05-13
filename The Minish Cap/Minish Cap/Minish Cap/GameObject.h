#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <SDL.h>
#include <string>

#include "Camera.h"

enum RenderTag
{
	UNTAGGED,
	BACKGROUND_SHADOWS,
	BACKGROUND,
	BACKGROUND_PARTICLES,
	ENTITY_SHADOWS,
	ENTITY,
	ENTITY_PARTICLES,
	FOREGROUND_SHADOWS,
	FOREGROUND,
	FORGROUND_PARTICLES,
	UI
};

class GameObject
{
protected:
	int opacity = 255;
public:
	int groupID = 0;

	float xPos = 0;
	float yPos = 0;

	SDL_Rect position = {0,0,0,0};
	SDL_Rect texturePos {0,0,0,0};
	std::string textureName = "";
	
	RenderTag renderTag;

	GameObject(SDL_Rect _pos) : position(_pos) {}
	GameObject(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag) : position(_pos), texturePos(_textPos), textureName(_textName), renderTag(_tag) {}
	GameObject(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag, int _groupID) : position(_pos), texturePos(_textPos), textureName(_textName), renderTag(_tag), groupID(_groupID) {}
	GameObject(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag, int _groupID, int _opacity) : position(_pos), texturePos(_textPos), textureName(_textName), renderTag(_tag), groupID(_groupID), opacity(_opacity) {}

	virtual void update() {}
	virtual void draw(SDL_Renderer ** _renderer);
};

#endif