#pragma once
#include "SDL.h"
#include "TextureManager.h"
class ColliderComponent;
class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool WP(const SDL_Rect& wrect, const SDL_Rect& pRect);
	static bool KP(const SDL_Rect& wrect, const SDL_Rect& pRect);
	static bool WP(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool KP(const ColliderComponent& colA, const ColliderComponent& colB);
};