#ifndef CAMERA
#define CAMERA

#include "SDL.h"

class Camera
{
private:
public:
	static SDL_Window ** window;
	static int xPositionOfset;
	static int yPositionOfset;
};

#endif // !CAMERA
