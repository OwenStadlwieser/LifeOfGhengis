#pragma once
#include "TextureManager.h"
#include <math.h>

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	// create surface
	SDL_Surface* tempSurface = IMG_Load(texture);
	if (!tempSurface)
	{
		SDL_Log("Unable to initialize loader: %s", IMG_GetError());
		return nullptr;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	// clean up
	SDL_FreeSurface(tempSurface);
	return tex;
}
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
};

void TextureManager::DrawTile(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip, float targetx, float targety, float positionx, float positiony)
{
	float dist = powf(powf(targetx - positionx, 2) + powf(targety - positiony, 2), 0.5);
	if (dist < 1500) {
		SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
		uint8_t colorMod = 60;
		if (dist > 255) {
			dist = 255;
		}
		else if (dist < 95) {
			dist = 95;
		}
		SDL_SetTextureColorMod(tex, colorMod, colorMod, colorMod);
		SDL_SetTextureAlphaMod(tex, dist);
		SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
	}
	else {
		SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
	}
};
void TextureManager::DrawSprite(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip, float targetx, float targety, float positionx, float positiony)
{
	float dist = powf(powf(targetx - positionx, 2) + powf(targety - positiony, 2), 0.5);
	if (dist < 1500) {
		SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
		uint8_t colorMod = 60;
		if (dist > 255 * 2.2) {
			dist = 255 * 2.2;
		}
		else if (dist < 95) {
			dist = 95;
		}
		SDL_SetTextureColorMod(tex, colorMod, colorMod, colorMod);
		SDL_SetTextureAlphaMod(tex, 255 - (dist / 2.2));
		SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
	}
	else {
		SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
	}
};