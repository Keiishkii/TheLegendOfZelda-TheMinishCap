#ifndef FILESELECTCURSOR
#define FILESELECTCURSOR

#include "GameObject.h"

class FileSelectCursor : public GameObject
{
private:
	int animationFrame;
public:
	FileSelectCursor(SDL_Rect _pos);

	virtual void update();
	virtual void draw(SDL_Renderer ** _renderer);
};

#endif // !FILESELECTCURSOR
