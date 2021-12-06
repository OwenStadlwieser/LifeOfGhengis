#pragma once
#include "../TextureManager.h"
#include "ECS.h"
#include "SDL_ttf.h"
#include "SDL.h"

class TextComponent : public Component
{
public: 
	SDL_Texture* texture;
	SDL_Rect destRect;
	Vector2D position;
	
	TextComponent() = default;
	~TextComponent()
	{
		SDL_DestroyTexture(texture);
	}
	TextComponent(int w, int h, int x, int y, int tsize, int tscale, int rgb[3], const char* text, SDL_Renderer* renderer, TTF_Font* Sans)
	{
        SDL_Color color = {rgb[0], rgb[1], rgb[2]};
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text, color);
		if (!surfaceMessage) {
			throw std::exception("text could not be loaded");
		}
		texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		if (!texture) {
			throw std::exception("text could not be loaded");
		}
		position.x = x;
		position.y = y;
		destRect.x = x;
		destRect.y = y;
		destRect.w = tscale * w;
		destRect.h = tscale * h;
	}
	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}
	void drawText() 
	{
		TextureManager::DrawText(texture, destRect, SDL_FLIP_NONE);
	}
};