#include "SoundManager.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

std::map<std::string, Mix_Chunk * > SoundManager::soundFXList;
std::map<std::string, Mix_Music * > SoundManager::musicList;

Mix_Chunk * SoundManager::currentSFX = nullptr;
Mix_Music * SoundManager::currentMusic = nullptr;

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
		loadSound("MC_Link_Sword1.wav", "MC_Link_Sword1") &&
		loadSound("MC_Link_Sword2.wav", "MC_Link_Sword2") &&
		loadSound("MC_Link_Sword3.wav", "MC_Link_Sword3") &&
		loadSound("MC_Emote_Exclaim.wav", "MC_Emote_Exclaim") &&
		loadSound("MC_Menu_Cursor.wav", "MC_Menu_Cursor") &&
		loadSound("MC_Shatter.wav", "MC_Shatter") &&
		loadSound("MC_Menu_Select.wav", "MC_Menu_Select")
	);

	return success;
}

bool SoundManager::loadMusic(std::string _path, std::string _name)
{
	bool foundFile = true;

	musicList[_name] = Mix_LoadMUS(("music/" + _path).c_str());
	
	if (musicList[_name] == nullptr)
	{
		foundFile = false;
		std::cout << "Failed to find file" << std::endl;
	}

	return foundFile;
}

bool SoundManager::loadSound(std::string _path, std::string _name)
{
	bool foundFile = true;

	soundFXList[_name] = Mix_LoadWAV(("SFX/" + _path).c_str());

	if (soundFXList[_name] == NULL)
	{
		foundFile = false;
	}

	return foundFile;
}

void SoundManager::playSound(std::string _name)
{
	Mix_PlayChannel(-1, soundFXList[_name], 0);
}

void SoundManager::playMusic(std::string _name)
{
	Mix_PlayMusic(musicList[_name], 0);
}

void SoundManager::playLoopedMusic(std::string _name)
{
	Mix_PlayMusic(musicList[_name], -1);
}

void SoundManager::stopMusic()
{
	Mix_HaltMusic();
}

void SoundManager::toggleMusicPause()
{
	if (currentMusic != nullptr)
	{
		if (!Mix_PlayingMusic())
		{
			Mix_PlayMusic(currentMusic, -1);
		}
		else if (Mix_PausedMusic())
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_PauseMusic();
		}
	}
}

void SoundManager::unloadAllAudio()
{
	std::map<std::string, Mix_Chunk * >::iterator soundItr = soundFXList.begin();
	std::map<std::string, Mix_Music * >::iterator musicItr = musicList.begin();

	for (soundItr = soundFXList.begin(); soundItr != soundFXList.end(); soundItr++)
	{
		delete soundItr->second;
	}

	for (musicItr = musicList.begin(); musicItr != musicList.end(); musicItr++)
	{
		delete musicItr->second;
	}

	soundFXList.clear();
	musicList.clear();
}