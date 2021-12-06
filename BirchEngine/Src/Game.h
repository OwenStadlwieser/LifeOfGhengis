#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include "SDL_image.h"
#include <vector>

class ColliderComponent;
class Game
{
public:
	Game();
	~Game();
	static bool isRunning;
	static bool alive;
	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	bool isAlive() { return alive;  }
	void render();
	void clean();
	void quit();
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static SDL_Rect camera;
	static TTF_Font* fontPtr;
	//static AssetManager* assets;
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupWomen,
		groupLabels,
		groupKid,
		groupText
	};
private:
	int cnt = 0;
	SDL_Window *window;
};