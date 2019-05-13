#ifndef FILESELECTBACKGROUND
#define FILESELECTBACKGROUND

#include "GameObject.h"

class FileSelectBackground : public GameObject
{
private:
	int animationFrame = 0;
public:
	FileSelectBackground(SDL_Rect _pos);

	void draw(SDL_Renderer ** _renderer);
};

#endif // !FILESELECTBACKGROUND
