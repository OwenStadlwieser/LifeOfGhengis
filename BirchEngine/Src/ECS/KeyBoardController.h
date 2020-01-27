#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "SpriteComponent.h"

class KeyBoardController : public Component
{
public:
	TransformComponent *transform;
	SpriteComponent *sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (Game::alive)
		{
			if (Game::event.type == SDL_KEYDOWN)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					transform->velocity.y = -1;
					if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_D])
					{
						sprite->Play("Walk");
					}
					else
					{
						sprite->Play("Idle");
					}
					break;
				case SDLK_a:
					transform->velocity.x = -1;
					sprite->Play("Walk");
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					break;
				case SDLK_d:
					transform->velocity.x = 1;
					sprite->Play("Walk");
					break;
				case SDLK_s:
					transform->velocity.y = 1;
					if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_D])
					{
						sprite->Play("Walk");
					}
					else
					{
						sprite->Play("Idle");
					}
					break;
				}
			}
			if (Game::event.type == SDL_KEYUP)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					transform->velocity.y = 0;
					if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_D])
					{
						sprite->Play("Walk");
					}
					else
					{
						sprite->Play("Idle");
					}
					break;
				case SDLK_a:
					transform->velocity.x = 0;
					sprite->Play("Idle");
					sprite->spriteFlip = SDL_FLIP_NONE;
					break;
				case SDLK_d:
					transform->velocity.x = 0;
					sprite->Play("Idle");
					break;
				case SDLK_s:
					transform->velocity.y = 0;
					if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_D])
					{
						sprite->Play("Walk");
					}
					else
					{
						sprite->Play("Idle");
					}
					break;
				case SDLK_ESCAPE:
					Game::isRunning = false;
					break;
				}
			}
		}
		else
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_p:
				Game::alive = true;
				break;
			}
		}
	}
};