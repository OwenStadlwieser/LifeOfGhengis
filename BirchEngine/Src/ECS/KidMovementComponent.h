#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "SpriteComponent.h"
#include <cmath>
class KidMovementComponent : public Component
{
public:
	TransformComponent *transform;
	SpriteComponent *sprite;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}
	void updatevelocity(float targetx, float targety)
	{
		float vecx = targetx - transform->position.x;
		float vecy = targety - transform->position.y;
		float length = sqrt(vecx*vecx + vecy * vecy);
		vecx = (vecx) / (length);
		vecy = (vecy) / (length);
		transform->velocity.x = vecx;
		transform->velocity.y = vecy;
		if (vecx > 0.3)
		{
			sprite->Play("Walk");
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		if (vecx < -0.3)
		{
			sprite->Play("Walk");
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
		}
	};
	void update() override
	{
		if (transform->position.x < 0)
		{
			transform->position.x = rand() % (2400 + 1 - 800) + 800;
		}
		if (transform->position.y < 0)
		{
			transform->position.y = rand() % (2400 + 1 - 800) + 800;
		}
		if (transform->position.y > 3200)
		{
			transform->position.y = rand() % (2400 + 1 - 800) + 800;
		}
		if (transform->position.x > 3200)
		{
			transform->position.x = rand() % (2400 + 1 - 800) + 800;
		}
	}
private:
	int cnt = 0;
};