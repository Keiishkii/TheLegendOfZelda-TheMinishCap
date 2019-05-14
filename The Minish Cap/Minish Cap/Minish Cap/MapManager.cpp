#include "MapManager.h"

#include <iostream>

std::map<std::string, Map * > MapManager::mapList;

void MapManager::loadAllMaps()
{
	mapList["RoyalCrypt"] = new Map("Maps/RoyalCrypt.txt");
}

Map * MapManager::getMap(std::string _name)
{
	if (mapList[_name] == nullptr)
	{
		std::cout << _name << " could not be loaded." << std::endl;
	}
	return mapList[_name];
}

void MapManager::unloadAllMaps()
{
	std::map<std::string, Map * >::iterator itr = mapList.begin();

	for (itr = mapList.begin(); itr != mapList.end(); itr++)
	{
		delete itr->second;
	}

	mapList.clear();
}