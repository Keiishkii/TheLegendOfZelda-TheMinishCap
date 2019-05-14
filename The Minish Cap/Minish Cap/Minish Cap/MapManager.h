#ifndef MAP_MANAGER
#define MAP_MANAGER

#include <string>
#include <map>

#include "Map.h"

class MapManager
{
private:
	static std::map<std::string, Map * > mapList;

public:
	static Map * getMap(std::string _name);
	static void loadAllMaps();
	static void unloadAllMaps();
};

#endif