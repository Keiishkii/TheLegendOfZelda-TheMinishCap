#include "SaveFileManager.h"

#include <iostream>

SaveFile SaveFileManager::save0;
SaveFile SaveFileManager::save1;
SaveFile SaveFileManager::save2;

void SaveFileManager::loadSaves()
{
	save0.loadFileData("Saves/save_0.txt");
	save0.name = "Save 0";
	save1.loadFileData("Saves/save_1.txt");
	save1.name = "Save 1";
	save2.loadFileData("Saves/save_2.txt");
	save2.name = "Save 2";
}

SaveFile * SaveFileManager::getSave(int _saveID)
{
	SaveFile * file = nullptr;

	switch (_saveID)
	{
	case 0:
		file = &save0;
		break;
	case 1:
		file = &save1;
		break;
	case 2:
		file = &save2;
		break;
	}

	return file;
}