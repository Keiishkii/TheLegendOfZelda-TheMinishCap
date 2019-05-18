#include "SaveFile.h"

#include <iostream>

#include <sstream>
#include <fstream>

//loads in this objects data from files
void SaveFile::loadFileData(std::string _saveName)
{
	//creates a file stream to load in the data
	std::ifstream stream;
	//opens the stream
	stream.open(_saveName);

	if (stream.is_open())
	{
		//a string used for determining the current line of the file
		std::string currentLine;

		//runs until reaching the bottom of the file
		while (std::getline(stream, currentLine))
		{
			// sets the string to the file streams input
			std::stringstream lineStream(currentLine);

			//compares the string to the variable names and inputs in the values if they are of the correct name.
			if (!currentLine.substr(0, 11).compare(0, 11, "#MaxHearts "))
			{
				std::string junk;
				// removes th first part of the line string and stores the rest as variable data.
				lineStream >> junk >> maxHearts;
			}
			else if (!currentLine.substr(0, 8).compare(0, 8, "#Hearts "))
			{
				std::string junk;
				// removes th first part of the line string and stores the rest as variable data.
				lineStream >> junk >> hearts;
			}
			else if (!currentLine.substr(0, 8).compare(0, 8, "#Arrows "))
			{
				std::string junk;
				// removes th first part of the line string and stores the rest as variable data.
				lineStream >> junk >> arrows;
			}
			else if (!currentLine.substr(0, 7).compare(0, 7, "#Bombs "))
			{
				std::string junk;
				// removes th first part of the line string and stores the rest as variable data.
				lineStream >> junk >> bombs;
			}
			else if (!currentLine.substr(0, 5).compare(0, 5, "#Map "))
			{
				std::string junk;
				// removes th first part of the line string and stores the rest as variable data.
				lineStream >> junk >> map;
			}
		}
	}
}

//Saves the data stored in this object to files.
void SaveFile::saveFileData(std::string _saveName)
{

}