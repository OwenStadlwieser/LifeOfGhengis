#include "TextureManager.h"
#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / 60;
	Uint32 frameStart;
	int frameTime;
	game = new Game();
	Game::alive = false;
	game->init("GameWindow", 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks(); // amount of time since start
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart; // time to run game updates
		// cap frame rate
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	game->quit();
	return 0;
}