#ifndef FILESELECTUINUMBER
#define FILESELECTUINUMBER

#include "GameObject.h"

class FileSelectUINumber : public GameObject
{
private:
	int fileID = 0;
public:
	FileSelectUINumber(SDL_Rect _pos, int fileID);

	virtual void update() {}
	virtual void draw(SDL_Renderer ** _renderer);
};

#endif // !FILESELECTUI
