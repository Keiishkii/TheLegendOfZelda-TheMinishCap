#ifndef SAVEFILEMANAGER
#define SAVEFILEMANAGER

#include <string>

#include "SaveFile.h"

class SaveFileManager
{
private:
public:
	static SaveFile save0;
	static SaveFile save1;
	static SaveFile save2;

	static void loadSaves();
	static SaveFile * getSave(int _saveID);
};

#endif // !SAVEFILEMANAGER
