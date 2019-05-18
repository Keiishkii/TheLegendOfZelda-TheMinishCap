#include "SoundManager.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

std::map<std::string, Mix_Chunk * > SoundManager::soundFXList;
std::map<std::string, Mix_Music * > SoundManager::musicList;

// 
Mix_Chunk * SoundManager::currentSFX = nullptr;
Mix_Music * SoundManager::currentMusic = nullptr;

// Loads in all the audio
bool SoundManager::loadAllAudio()
{
	bool success;
	
	success = 
	(
		//Load music
		loadMusic("01 Title Screen.mp3", "01 Title Screen") &&
		loadMusic("02 File Select.mp3", "02 File Select") &&
		loadMusic("47 Royal Crypt.mp3", "47 Royal Crypt") &&

		//Load sound
		loadSound("MC_Rupee.wav", "MC_Rupee") &&
		loadSound("MC_Rupee_Bounce.wav", "MC_Rupee_Bounce") &&
		loadSound("MC_Link_Sword1.wav", "MC_Link_Sword1") &&
		loadSound("MC_Link_Sword2.wav", "MC_Link_Sword2") &&
		loadSound("MC_Link_Sword3.wav", "MC_Link_Sword3") &&
		loadSound("MC_Emote_Exclaim.wav", "MC_Emote_Exclaim") &&
		loadSound("MC_Menu_Cursor.wav", "MC_Menu_Cursor") &&
		loadSound("MC_Shatter.wav", "MC_Shatter") &&
		loadSound("MC_Menu_Select.wav", "MC_Menu_Select")
	);

	// returns false if one of the audio files fails to load
	return success;
}

// loads in a peice of music when given a path and a name
bool SoundManager::loadMusic(std::string _path, std::string _name)
{
	bool foundFile = true;

	// adds a peice of music the the music map
	musicList[_name] = Mix_LoadMUS(("music/" + _path).c_str());
	
	// checks to see if the music was correctly added
	if (musicList[_name] == nullptr)
	{
		foundFile = false;
		std::cout << "Failed to find file" << std::endl;
	}

	return foundFile;
}

// loads in a sound effect when given a path and a name
bool SoundManager::loadSound(std::string _path, std::string _name)
{
	bool foundFile = true;

	// adds a peice of music the the sound effect map
	soundFXList[_name] = Mix_LoadWAV(("SFX/" + _path).c_str());

	// checks to see if the sound effect was correctly added
	if (soundFXList[_name] == NULL)
	{
		foundFile = false;
	}

	return foundFile;
}

// plays a sound once
void SoundManager::playSound(std::string _name)
{
	Mix_PlayChannel(-1, soundFXList[_name], 0);
}

// plays some music once
void SoundManager::playMusic(std::string _name)
{
	Mix_PlayMusic(musicList[_name], 0);
}

// loops through the music
void SoundManager::playLoopedMusic(std::string _name)
{
	Mix_PlayMusic(musicList[_name], -1);
}

// stops all the music 
void SoundManager::stopMusic()
{
	Mix_HaltMusic();
}

// pauses or plays the music depending on its current state
void SoundManager::toggleMusicPause()
{
	if (currentMusic != nullptr)
	{
		// checks if the music was even playing
		if (!Mix_PlayingMusic())
		{
			// plays the music
			Mix_PlayMusic(currentMusic, -1);
		}
		// checks if the music is currently paused
		else if (Mix_PausedMusic())
		{
			// resumes the music
			Mix_ResumeMusic();
		}
		else
		{
			// pauses the music
			Mix_PauseMusic();
		}
	}
}

// unlaods all the audio on the programs exit
void SoundManager::unloadAllAudio()
{
	std::map<std::string, Mix_Chunk * >::iterator soundItr = soundFXList.begin();
	std::map<std::string, Mix_Music * >::iterator musicItr = musicList.begin();

	// iterates through the sound effect vector removing and deleting the files
	for (soundItr = soundFXList.begin(); soundItr != soundFXList.end(); soundItr++)
	{
		delete soundItr->second;
	}

	// iterates through the music vector removing and deleting the files
	for (musicItr = musicList.begin(); musicItr != musicList.end(); musicItr++)
	{
		delete musicItr->second;
	}

	soundFXList.clear();
	musicList.clear();
}