#include "Collision.h"
#include "ECS/ColliderComponent.h"
#include "TextureManager.h"
#include <iostream>
bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		(recA.x + (recA.w) >= recB.x + 20 &&
		recB.x + recB.w - 20>= recA.x &&
		recA.y + recA.h >= recB.y + 10&&
		recB.y + recB.h - 10 >= recA.y)
		)
	{
		return true;
	}
	return false;
}
bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		std::cout << colA.tag << " hit " << colB.tag << std::endl;
		return true;
	}
	return false;
}
bool Collision::WP(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		(recA.x + (recA.w) -20 >= recB.x + 20 &&
			recB.x + recB.w - 20 >= recA.x +20&&
			recA.y + recA.h - 10 >= recB.y + 10 &&
			recB.y + recB.h -10 >= recA.y + 10)
		)
	{
		return true;
	}
	return false;
}
bool Collision::WP(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		std::cout << colA.tag << " interacted with a " << colB.tag << std::endl;
		return true;
	}
	return false;
}
bool Collision::KP(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		(recA.x + (recA.w) - 23 >= recB.x  + 23&&
			recB.x + recB.w - 23 >= recA.x + 23 &&
			recA.y + recA.h -10>= recB.y + 10 &&
			recB.y + recB.h -10>= recA.y +10)
		)
	{
		return true;
	}
	return false;
}
bool Collision::KP(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		std::cout << colA.tag << " stopped " << colB.tag << std::endl;
		return true;
	}
	return false;
}