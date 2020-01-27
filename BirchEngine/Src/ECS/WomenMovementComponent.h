#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "SpriteComponent.h"

class WomenMovementComponent : public Component
{
public:
	int pathlength;
	int count;
	TransformComponent *transform;
	SpriteComponent *sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (pathlength == 0)
		{
			pathlength = rand() % (600 + 1 - 30) + 30;
			float x = rand() % 3;
			float y = rand() % 3;
			if (x == 2)
			{
				transform->velocity.x = 1;
				sprite->Play("Walk");
			}
			else if (x == 1)
			{
				transform->velocity.x = -1;
				sprite->Play("Idle");
			}
			else
			{
				transform->velocity.x = 0;
				sprite->Play("Idle");
			}
			if (y == 2)
			{
				transform->velocity.y = 1;
			}
			else if (y == 1)
			{
				transform->velocity.y = -1;
			}
			else
			{
				transform->velocity.y = 0;
			}
		}
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
			transform->position.y = rand()  % (2400 + 1 - 800) + 800;
		}
		if (transform->position.x > 3200)
		{
			transform->position.x = rand()  % (2400 + 1 - 800) + 800;
		}
		count++;
		if (count == pathlength)
		{
			pathlength = 0;
		}
	}
};