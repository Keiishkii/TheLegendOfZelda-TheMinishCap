#ifndef FILESELECTSTATE
#define FILESELECTSTATE

#include <SDL.h>
#include <vector>

#include "GameObject.h"

class FileSelect
{
private:
	static std::vector<GameObject * > objectList;

	static void addObjectToList(GameObject * _object);
	static void inputs();
	static void moveUpSelected();
	static void moveDownSelected();

	static void loadSelectedFile();

	static void removeFileDisplay();
	static void displayFileContent();
public:
	static int selectedSave;

	static void loadState();
	static void unloadState();
	static void update();
	static void display(SDL_Renderer** _renderer);
};

#endif

