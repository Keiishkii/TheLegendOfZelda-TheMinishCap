#ifndef SAVEFILE
#define SAVEFILE

#include <string>

class SaveFile
{
public:
	std::string name;
	std::string map;

	int maxHearts = 12;
	int hearts = 12;

	int rupees = 0;
	int bombs = 0;
	int arrows = 0;

public:
	void loadFileData(std::string _saveName);
	void saveFileData(std::string _saveName);

	int getMaxHealth() { return maxHearts; }
	int getCurrentHealth() { return hearts; }

	int getRupees() { return rupees; }
	int getBombs() { return bombs; }
	int getArrows() { return arrows; }
};

#endif // !SAVEFILE
