#pragma once
#include "Game.h"

class TextureManager {
public:
	// valid for all members
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};