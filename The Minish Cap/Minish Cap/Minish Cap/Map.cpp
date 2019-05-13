#include "Map.h"

#include <fstream>
#include <sstream>
#include <algorithm>

#include "Debug.h"

Map::Map(std::string _path)
{
	name = _path;
	loadFromFile(_path);
}

Room * Map::getRoom(int _roomID)
{
	return roomList.at(_roomID - 1);
}

void Map::loadFromFile(std::string _mapName)
{
	std::ifstream stream;
	stream.open(_mapName);

	std::string mapName;
	std::string mapSpriteSheet;

	Room * currentRoom = nullptr;

	if (stream.is_open())
	{
		std::string currentLine;

		while (std::getline(stream, currentLine))
		{
			std::stringstream lineStream(currentLine);

			if (!currentLine.substr(0, 6).compare(0, 6, "#Room "))
			{
				std::string junk;

				int room;

				int xPos;
				int yPos;
				int width;
				int height;

				int textureXPos;
				int textureYPos;
				int textureWidth;
				int textureHeight;

				lineStream >> junk >> room >> xPos >> yPos >> width >> height >> textureXPos >> textureYPos >> textureWidth >> textureHeight;

				currentRoom = new Room(SDL_Rect{ xPos, yPos, width, height }, SDL_Rect{ textureXPos, textureYPos, textureWidth, textureHeight }, "", BACKGROUND, room);

				roomList.push_back(currentRoom);
			}
			if (!currentLine.substr(0, 6).compare(0, 6, "-Wall "))
			{
				std::string junk;

				int xPos;
				int yPos;
				int width;
				int height;

				lineStream >> junk >> xPos >> yPos >> width >> height;

				currentRoom->addWall(SDL_Rect{ xPos, yPos, width, height });
			}
			if (!currentLine.substr(0, 9).compare(0, 9, "#MapName "))
			{
				std::string junk;
				lineStream >> junk >> mapName;				
			}
			if (!currentLine.substr(0, 16).compare(0, 16, "#MapSpriteSheet "))
			{
				std::string junk;
				lineStream >> junk >> mapSpriteSheet;
			}
			if (!currentLine.substr(0, 10).compare(0, 10, "#MapMusic "))
			{
				std::string junk;
				lineStream >> junk >> mapMusic; 
				std::replace(mapMusic.begin(), mapMusic.end(), '-', ' ');
			}
			if (!currentLine.substr(0, 13).compare(0, 13, "#DefaultRoom "))
			{
				std::string junk;
				lineStream >> junk >> defaultRoom;
			}
			if (!currentLine.substr(0, 14).compare(0, 14, "#DefaultSpawn "))
			{
				std::string junk;
				lineStream >> junk >> defaultX >> defaultY;
			}
		}
	}

	std::vector<Room * >::iterator itr = roomList.begin();

	for (itr = roomList.begin(); itr < roomList.end(); itr++)
	{
		(*itr)->textureName = mapSpriteSheet;
	}
}