#ifndef FILESELECTUI
#define FILESELECTUI

#include "GameObject.h"

class FileSelectUI : public GameObject
{
private:
	int fileID = 0;
public:
	FileSelectUI(SDL_Rect _pos, int fileID);

	virtual void update() {}
	virtual void draw(SDL_Renderer ** _renderer);
};

#endif // !FILESELECTUI
