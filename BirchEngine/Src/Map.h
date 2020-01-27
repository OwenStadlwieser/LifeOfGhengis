#pragma once
#include <string>
#include "AssetManager.h"
class Map
{
public:
	Map(const char* mfp, int ms, int ts);
	~Map();
	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcx, int srcy, int x, int y);
private:
	const char* mapFilePath;
	int tileSize;
	int mapScale;
};