#ifndef RUPEE
#define RUPEE

#include "Entity.h"

class Rupee : public Entity
{
private:
	int amount = 1;
	int animationFrame = 0;
public:
	Rupee(SDL_Rect _pos, SDL_Rect _textPos, std::string _textName, RenderTag _tag, int _amount);
	int getAmount() { return amount; }
	void update();
	void draw(SDL_Renderer ** _renderer);
	~Rupee();
};

#endif // !RUPEE
