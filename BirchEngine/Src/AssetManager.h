#pragma once
#include "ECS\ECS.h"
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"

class AssetManager
{
public:
	AssetManager(Manager* man);
	SDL_Texture* GetTexture(std::string id);
	~AssetManager();

	void AddTexture(std::string id, const char* path);

private:
	// dictionary
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
};