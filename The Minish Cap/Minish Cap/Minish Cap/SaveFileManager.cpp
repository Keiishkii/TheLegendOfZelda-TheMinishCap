#include "SaveFileManager.h"

#include <iostream>

// save files
SaveFile SaveFileManager::save0;
SaveFile SaveFileManager::save1;
SaveFile SaveFileManager::save2;

// Loads in all the saves from there files
void SaveFileManager::loadSaves()
{
	save0.loadFileData("Saves/save_0.txt");
	save0.getName() = "Save 0";
	save1.loadFileData("Saves/save_1.txt");
	save1.getName() = "Save 1";
	save2.loadFileData("Saves/save_2.txt");
	save2.getName() = "Save 2";
}

// returns the save based on the ID given
SaveFile * SaveFileManager::getSave(int _saveID)
{
	SaveFile * file = nullptr;

	// checks all save IDs against the given ID and sets file to that save
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
	// returns the file
	return file;
}