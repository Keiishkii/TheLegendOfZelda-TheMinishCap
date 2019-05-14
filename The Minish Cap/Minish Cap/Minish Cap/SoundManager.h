#ifndef SOUNDMANAGER
#define SOUNDMANAGER

#include <SDL_mixer.h>
#include <map>

class SoundManager
{
private:
	static std::map<std::string, Mix_Chunk * > soundFXList;
	static std::map<std::string, Mix_Music * > musicList;

	static Mix_Chunk * currentSFX;
	static Mix_Music * currentMusic;

	static bool loadSound(std::string _path, std::string _name);
	static bool loadMusic(std::string _path, std::string _name);
public:
	static bool loadAllAudio();
	static void unloadAllAudio();

	static void playSound(std::string _name);
	static void playMusic(std::string _name);
	static void playLoopedMusic(std::string _name);

	static void stopMusic();

	static void toggleMusicPause();
};

#endif // !SOUNDMANAGER
