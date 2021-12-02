#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include "ECS\ECS.h"
#include "ECS\Components.h"
extern Manager manager;
Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp), tileSize(ts), mapScale(ms)
{
}
Map::~Map()
{

}
void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile, tile1, tile2;
	std::fstream mapFile;
	mapFile.open(path);
	if (!mapFile.is_open())
	{
		throw new std::exception("Rule file could not be opened");
	}
	int srcX, srcY;
	int val1, val2, val3;
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			mapFile.get(tile1);
			mapFile.get(tile2);
			val1 = atoi(&tile);
			val2 = atoi(&tile1);
			if (tile2 != ',')
			{
				val3 = atoi(&tile2);
				srcX = ((val1*100 + val2*10 + val3 - 1) % (tileSize + 1)) * (tileSize+1);
				if ((val1 * 100 + val2 * 10 + val3 - 1) == 189)
				{
					srcY = ((val1 * 100 + val2 * 10 + val3 - 1) - srcX);
				}
				else
				{
					srcY = ((val1 * 100 + val2 * 10 + val3 - 1) - ((val1 * 10 + val2 + val3 - 1) % (tileSize +1)));
				}
				if (tile2 != '\n')
				{
					mapFile.ignore();
				}
			}
			else
			{
				val3 = 0;
				srcX = ((val1*10 + val2 + val3 - 1) % (tileSize + 1)) * (tileSize + 1);
				srcY = ((val1*10 + val2 + val3 - 1) - ((val1 * 10 + val2 + val3 - 1) % (tileSize + 1)));
			}
			AddTile(srcX - 7, srcY - 4, x * tileSize * mapScale, y * tileSize * mapScale);
		}
	};
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			mapFile.get(tile1);
			mapFile.get(tile2);
			val1 = atoi(&tile);
			val2 = atoi(&tile1);
			if (tile2 != ',')
			{
				val3 = atoi(&tile2);
				srcX = ((val1 * 100 + val2 * 10 + val3 - 1) % (tileSize + 1)) * (tileSize + 1);
				if ((val1 * 100 + val2 * 10 + val3 - 1) == 189)
				{
					srcY = ((val1 * 100 + val2 * 10 + val3 - 1) - srcX);
				}
				else
				{
					srcY = ((val1 * 100 + val2 * 10 + val3 - 1) - ((val1 * 10 + val2 + val3 - 1) % (tileSize + 1)));
				}
				if (tile2 != '\n')
				{
					mapFile.ignore();
				}
			}
			else
			{
				val3 = 0;
				srcX = ((val1 * 10 + val2 - 1) % (tileSize + 1)) * (tileSize + 1);
				srcY = ((val1 * 10 + val2 - 1) - ((val1 * 10 + val2 - 1) % (tileSize + 1)));
			}
			if (val1 + val2 + val3 != 0)
			{
				AddTile(0x00000022 - 7, 0x00000116 - 4, x * tileSize * mapScale, y * tileSize * mapScale);
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * (tileSize * mapScale), y *tileSize * mapScale, tileSize * mapScale);
				tcol.addGroup(Game::groupColliders);
			}
			
		}
	};



	mapFile.close();
}
void Map::AddTile(int srcx, int srcy, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcx, srcy, x, y,tileSize, mapScale, mapFilePath);
	tile.addGroup(Game::groupMap);
}