#pragma once
#include "../TextureManager.h"
#include "Components.h"
#include "SDL.h"
#include "Animation.h"
#include <map>
class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	bool animated = false;
	int frames = 0;
	int speed = 100;
public:
	int animIndex = 0;
	std::map<const char*, Animation> animations;
	SpriteComponent() = default;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	SpriteComponent(const char* path)
	{
		setText(path);
	};
	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;
		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);
		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		Play("Idle");
		setText(path);
	};
	~SpriteComponent()
	{
		
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		destRect.w = transform->width *transform->scale;
		destRect.h = transform->height *transform->scale;
	}
	void setDest()
	{
		destRect.w = transform->width;
		destRect.h = transform->height;
	}
	void setText(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}
	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		srcRect.y = animIndex * transform->height;
		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}
	void drawSprite(float targetx, float targety)
	{
		TextureManager::DrawSprite(texture, srcRect, destRect, spriteFlip, targetx, targety, transform->position.x, transform->position.y);
	}
	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		speed = animations[animName].speed;
		animIndex = animations[animName].index;
	}
};