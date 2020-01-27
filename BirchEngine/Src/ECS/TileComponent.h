#pragma once
#include "../TextureManager.h"
#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component
{
public: 
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}
	TileComponent(int srcx, int srcy, int x, int y, int tsize, int tscale, const char* path)
	{
		position.x = x;
		position.y = y;
		texture = TextureManager::LoadTexture(path);
		srcRect.x = srcx;
		srcRect.y = srcy;
		srcRect.w = tsize;
		srcRect.h = tsize;
		destRect.x = x;
		destRect.y = y;
		destRect.w = destRect.h = tscale * tsize;
	}
	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};