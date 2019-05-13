#ifndef MAP
#define MAP

#include <vector>
#include <string>

#include "Room.h"

class Map
{
private:
	std::string name;
	std::vector<Room * > roomList;
	void loadFromFile(std::string _name);
public:
	int defaultRoom = 0;
	int defaultX = 0;
	int defaultY = 0;

	Room * getRoom(int _roomID);

	Map(std::string _name);
	std::vector<Room * > * getRoomList() { return &roomList; }
	std::string getName() { return name; }
};

#endif