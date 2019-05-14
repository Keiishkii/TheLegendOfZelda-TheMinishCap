#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <SDL.h>
#include <string>

#include "Camera.h"

enum RenderTag
{
	TAG_UNTAGGED,
	TAG_BACKGROUND_SHADOWS,
	TAG_BACKGROUND,
	TAG_BACKGROUND_PARTICLES,
	TAG_ENTITY_SHADOWS,
	TAG_GROUND_ENTITY,
	TAG_ENTITY,
	TAG_AIR_ENTITY,
	TAG_ENTITY_PARTICLES,
	TAG_FOREGROUND_SHADOWS,
	TAG_FOREGROUND,
	TAG_FORGROUND_PARTICLES,
	TAG_UI
};

class GameObject
{
private:
	static unsigned int ID_Counter;
protected:
	int opacity = 255;
public:
	int ID;
	int groupID = 0;

	float xPos = 0;
	float yPos = 0;

	SDL_Rect position = {0,0,0,0};
	SDL_Rect texturePos {0,0,0,0};
	std::string textureName = "";
	
	RenderTag renderTag;

	GameObject(SDL_Rect _pos) : position(_pos) { ID = ID_Counter++; }
	GameObject(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag) : position(_pos), texturePos(_textPos), textureName(_textName), renderTag(_tag) { ID = ID_Counter++; }
	GameObject(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag, int _groupID) : position(_pos), texturePos(_textPos), textureName(_textName), renderTag(_tag), groupID(_groupID) { ID = ID_Counter++; }
	GameObject(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag, int _groupID, int _opacity) : position(_pos), texturePos(_textPos), textureName(_textName), renderTag(_tag), groupID(_groupID), opacity(_opacity) { ID = ID_Counter++; }

	virtual void update() {}
	virtual void lateUpdate() {}
	virtual void draw(SDL_Renderer ** _renderer);
};

#endif