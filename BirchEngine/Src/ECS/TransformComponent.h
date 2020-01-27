#pragma once
#include "Components.h"
#include "../Vector2D.h"
#include <iostream>
#include <cmath>
class TransformComponent : public Component
{	
public:
	Vector2D velocity;
	int speed = 3;
	int height = 32;
	int width = 32;
	int scale = 1;
	Vector2D position;

	TransformComponent()
	{
		position.Zero();
	}
	TransformComponent(int sc)
	{
		position.x = 800;
		position.y = 320;
		scale = sc;
	}
	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	TransformComponent(float x, float y, int h, int w, int sc, int sp)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
		speed = sp;
	}
	void init() override
	{
		velocity.Zero();
	}
	void update() override
	{
		int length = sqrt((velocity.x*velocity.x) + (velocity.y*velocity.y));
		if (length != 0)
		{
			position.x += velocity.x / length * speed;
			position.y += velocity.y / length * speed;
		}
		else
		{
			position.x += velocity.x * speed;
			position.y += velocity.y * speed;
		}
	}
	void setVelocity(float vx, float vy)
	{
		velocity.x = vx;
		velocity.y = vy;
	}
};