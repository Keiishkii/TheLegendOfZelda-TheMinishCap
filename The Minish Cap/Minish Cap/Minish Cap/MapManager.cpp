#include "MapManager.h"

#include <iostream>

std::map<std::string, Map * > MapManager::mapList;

// loads in all the maps in the game
void MapManager::loadAllMaps()
{
	mapList["RoyalCrypt"] = new Map("Maps/RoyalCrypt.txt");
}

// returns the map when given a name
Map * MapManager::getMap(std::string _name)
{
	if (mapList[_name] == nullptr)
	{
		std::cout << _name << " could not be loaded." << std::endl;
	}
	return mapList[_name];
}

// unloads all the maps in the game
void MapManager::unloadAllMaps()
{
	std::map<std::string, Map * >::iterator itr = mapList.begin();

	// iterates thorugh the list and deletes the maps then clears the list
	for (itr = mapList.begin(); itr != mapList.end(); itr++)
	{
		delete itr->second;
	}

	mapList.clear();
}