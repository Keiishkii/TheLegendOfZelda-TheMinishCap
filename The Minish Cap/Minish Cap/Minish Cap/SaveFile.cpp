#include "SaveFile.h"

#include <iostream>

#include <sstream>
#include <fstream>

void SaveFile::loadFileData(std::string _saveName)
{
	std::ifstream stream;
	stream.open(_saveName);

	if (stream.is_open())
	{
		std::string currentLine;

		while (std::getline(stream, currentLine))
		{
			std::stringstream lineStream(currentLine);

			if (!currentLine.substr(0, 11).compare(0, 11, "#MaxHearts "))
			{
				std::string junk;
				lineStream >> junk >> maxHearts;
			}
			else if (!currentLine.substr(0, 8).compare(0, 8, "#Hearts "))
			{
				std::string junk;
				lineStream >> junk >> hearts;
			}
			else if (!currentLine.substr(0, 8).compare(0, 8, "#Arrows "))
			{
				std::string junk;
				lineStream >> junk >> arrows;
			}
			else if (!currentLine.substr(0, 7).compare(0, 7, "#Bombs "))
			{
				std::string junk;
				lineStream >> junk >> bombs;
			}
			else if (!currentLine.substr(0, 5).compare(0, 5, "#Map "))
			{
				std::string junk;
				lineStream >> junk >> map;
			}
		}
	}
}

void SaveFile::saveFileData(std::string _saveName)
{

}