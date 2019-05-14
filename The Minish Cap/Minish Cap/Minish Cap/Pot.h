#ifndef POT
#define POT

#include "Entity.h"

class Pot : public Entity
{
private:

public:
	Pot(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag);
	void update();
	void lateUpdate();
	void death();
};

#endif // !ENTITY
