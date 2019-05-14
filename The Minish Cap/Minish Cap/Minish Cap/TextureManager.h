#ifndef TEXTUREMANAGER
#define TEXTUREMANAGER

#include <SDL.h>
#include <string>
#include <map>

class TextureManager
{
private:
	static std::map<std::string, SDL_Texture * > spriteMapList;
	static bool loadTexture(std::string _path, std::string _name, SDL_Renderer ** _renderer);
public:
	static bool loadAllTextures(SDL_Renderer ** _renderer);
	static void unloadAllTextures();
	static SDL_Texture * getTexture(std::string _name);
};

#endif // !TEXTUREMANAGER
