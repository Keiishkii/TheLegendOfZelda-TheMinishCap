#include "Map.h"

#include <fstream>
#include <sstream>
#include <algorithm>

#include "Pot.h"

// constuctor for map
Map::Map(std::string _path)
{
	name = _path;
	loadFromFile(_path);
}

// retursn a room based on the number passed in
Room * Map::getRoom(int _roomID)
{
	// returns the object at the index of _roomID
	return roomList.at(_roomID - 1);
}

// loads in the map from a file name
void Map::loadFromFile(std::string _mapName)
{
	//creates a file stream and opens it
	std::ifstream stream;
	stream.open(_mapName);

	std::string mapName;
	std::string mapSpriteSheet;

	Room * currentRoom = nullptr;
	int currentRoomPositionX = 0;
	int currentRoomPositionY = 0;

	// checks to see if the program could open the file
	if (stream.is_open())
	{
		// string for the current line in the file
		std::string currentLine;

		// runs for each line in the file
		while (std::getline(stream, currentLine))
		{
			//sets the current line to the string
			std::stringstream lineStream(currentLine);

			//Checks to see if the line starts with Specific names, if so creates an object or sets a variable based on the data following the lines type
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

				// Reads in the room and sets its bounds and textures based on the infomation in the file
				lineStream >> junk >> room >> xPos >> yPos >> width >> height >> textureXPos >> textureYPos >> textureWidth >> textureHeight;

				currentRoomPositionX = xPos;
				currentRoomPositionY = yPos;

				// creates a Room game object based on the values
				currentRoom = new Room(SDL_Rect{ xPos, yPos, width, height }, SDL_Rect{ textureXPos, textureYPos, textureWidth, textureHeight }, "", TAG_BACKGROUND, room);

				//adds the room to the room list
				roomList.push_back(currentRoom);
			}
			if (!currentLine.substr(0, 6).compare(0, 6, "-Wall "))
			{
				std::string junk;

				int xPos;
				int yPos;
				int width;
				int height;

				//gets the bounds for a new wall collision box 
				lineStream >> junk >> xPos >> yPos >> width >> height;

				//adds the SDL rectanlge of the wall the list
				currentRoom->addWall(SDL_Rect{ xPos, yPos, width, height });
			}
			if (!currentLine.substr(0, 5).compare(0, 5, "-Pot "))
			{
				std::string junk;

				int xPos;
				int yPos;
				int width;
				int height;

				lineStream >> junk >> xPos >> yPos >> width >> height;
				// Adds a pot to the respawning list
				currentRoom->addRespawning(new Pot(SDL_Rect{ xPos + currentRoomPositionX, yPos + currentRoomPositionY, width, height }, SDL_Rect{ 0, 0, 16, 16 }, "Pot", TAG_GROUND_ENTITY));
			}
			if (!currentLine.substr(0, 9).compare(0, 9, "#MapName "))
			{
				std::string junk;
				// sets the maps name
				lineStream >> junk >> mapName;				
			}
			if (!currentLine.substr(0, 16).compare(0, 16, "#MapSpriteSheet "))
			{
				std::string junk;
				// sets the name of the maps sprite sheet
				lineStream >> junk >> mapSpriteSheet;
			}
			if (!currentLine.substr(0, 10).compare(0, 10, "#MapMusic "))
			{
				std::string junk;
				// sets the name of the music to be played when entering the map
				lineStream >> junk >> mapMusic; 
				// replaces the dashes with spaces
				std::replace(mapMusic.begin(), mapMusic.end(), '-', ' ');
			}
			if (!currentLine.substr(0, 13).compare(0, 13, "#DefaultRoom "))
			{
				std::string junk;
				// sets the default spawn room for the player
				lineStream >> junk >> defaultRoom;
			}
			if (!currentLine.substr(0, 14).compare(0, 14, "#DefaultSpawn "))
			{
				std::string junk;
				// sets the default spawn position
				lineStream >> junk >> defaultX >> defaultY;
			}
		}
	}

	// iteratees though the room list setting all of there spritemaps the the maps texturemap.
	std::vector<Room * >::iterator itr = roomList.begin();

	for (itr = roomList.begin(); itr < roomList.end(); itr++)
	{
		(*itr)->textureName = mapSpriteSheet;
	}
}