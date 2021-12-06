
#include "Game.h"
#include "GameObject.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
//LINK2019 resave gameobject !!!
Map* map;
SDL_Renderer* Game::renderer = nullptr;
Manager manager;
auto& newPlayer(manager.addEntity());
auto& titleScreen(manager.addEntity());
SDL_Event Game::event;
SDL_Rect Game::camera = { 400, 1000, 800, 640 };
bool Game::isRunning = true;
bool Game::alive = false;
int color[3] = { 255, 0, 0 };
TTF_Font* Game::fontPtr = nullptr;

Game::Game()
{}

Game::~Game()
{}


void Game::init(const char* title, int width, int height, bool fullscreen)
{
	TTF_Init();
	Game::fontPtr = TTF_OpenFont("./assets/OpenSans.ttf", 24);
	if (!Game::fontPtr) {
		throw std::exception("font could not be loaded");
	}
	int flags = 0;
	std::cout << "Welcome to the life of Ghengis" << std::endl;
	std::cout << "The goal of the game is to create a swarm by interacting with the women in the red shirt." << std::endl;
	std::cout << "Unfortunately your swarm does not like you and will attempt to kill you!" << std::endl;
	std::cout << "Use WASD for controls, press P to play!" << std::endl;
	std::cout << "Press 'esc' to quit!" <<  std::endl;
	std::cout << "Developed by Owen Stadlwieser" << std::endl;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	map = new Map("assets/tileset.png", 4, 16);

	map->LoadMap("assets/newmap4.tmx", 50, 50);
	newPlayer.addComponent<TransformComponent>(2);
	newPlayer.addComponent<SpriteComponent>("assets/player_anims.png",true);
	newPlayer.addComponent<KeyBoardController>();
	newPlayer.addComponent<ColliderComponent>("player");
	const char* stringArr[] = {
		"The goal of the game is to create a swarm by interacting with the women in the red shirt.",
		"Unfortunately your swarm does not like you and will attempt to kill you!",
		"Use WASD for controls, press P to play!",
		"Press 'esc' to quit!",
		"Developed by Owen Stadlwieser"
	};
	auto& text(manager.addEntity());
	text.addComponent<TextComponent>(550, 100, 0, 0, 1, 1, color, "Welcome to The Life of Ghengis", renderer, Game::fontPtr);
	text.addGroup(Game::groupText);
	for (int i = 0; i < 5; i++) {
		int width = 500;
		int height = 30;
		if (i > 2) {
			width = 300;
		}
		auto& text(manager.addEntity());
		text.addComponent<TextComponent>(width, height, 0, 100 +  i * 30, 1, 1, color, stringArr[i], renderer, Game::fontPtr);
		text.addGroup(Game::groupText);
	}
	newPlayer.addGroup(groupPlayers);
	for (int i = 0; i < 30; i++)
	{
		auto& women(manager.addEntity());
		float x  = 128.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3072)));
		float y = 128.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3072)));
		women.addComponent<TransformComponent>(x, y, 32, 32, 2, rand() % (3 + 1 - 1) + 1);
		women.addComponent<SpriteComponent>("assets/player_anims2.png", true);
		women.addComponent<ColliderComponent>("women");
		women.addComponent<WomenMovementComponent>();
		women.addGroup(Game::groupWomen);
	}
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& womens(manager.getGroup(Game::groupWomen));
auto& kids(manager.getGroup(Game::groupKid));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& text(manager.getGroup(Game::groupText));
void Game::handleEvents()
{
	

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	case SDL_KEYUP:
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_p:
			if (Game::alive == false)
			{
				clean();
				init("GameWindow", 800, 640, false);
				Game::alive = true;
			}
			break;
		}
	default:
		break;
	}

}

void Game::update()
{
	SDL_Rect playerCol = newPlayer.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = newPlayer.getComponent<TransformComponent>().position;

	
	if (Game::alive)
	{
		manager.refresh();
		manager.update();
		for (auto& t : text) {
			t->destroy();
		}
		for (auto& c : colliders)
		{
			SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
			if (Collision::AABB(cCol, playerCol))
			{
				std::cout << "hit wall" << std::endl;
				newPlayer.getComponent<TransformComponent>().position = playerPos;
			}
		}
		for (auto& w : womens)
		{
			SDL_Rect wCol = w->getComponent<ColliderComponent>().collider;
			if (Collision::WP(wCol, playerCol))
			{
				auto& kid(manager.addEntity());
				float x = 128.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3072)));
				float y = 128.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3072)));
				w->getComponent<TransformComponent>().position.x = x;
				w->getComponent<TransformComponent>().position.y = y;
				kid.addComponent<TransformComponent>(x, y, 32, 32, 2, rand() % (2 + 1 - 1) + 1);
				kid.addComponent<SpriteComponent>("assets/player_anims3.png", true);
				kid.addComponent<ColliderComponent>("kid");
				kid.addComponent<KidMovementComponent>();
				kid.addGroup(Game::groupKid);
				Game::cnt++;
				std::cout << Game::cnt << std::endl;
				std::cout << "Swarm size: " << Game::cnt <<  std::endl;
			}

		}
		int i = 0;
		for (auto& k : kids)
		{
			k->getComponent<KidMovementComponent>().updatevelocity(playerPos.x - 20 * Game::cnt / 2 + 20 * i + rand() % (30 + 1 - 30) - 30,
				playerPos.y - 20 * Game::cnt / 2 + 20 * i + rand() % (30 + 1 - 30) - 30);
			i++;
			SDL_Rect kCol = k->getComponent<ColliderComponent>().collider;
			if (Collision::KP(kCol, playerCol))
			{
				char buffer[50];
				sprintf(buffer, "You created a swarm of %d", Game::cnt);
				const char* stringArr[] = {
					buffer,
					"Press P to play again",
					"Press 'esc' to quit!"
				};
				int width = 300;
				int height = 30;
				int screenW = 800;
				int screenH = 640;
				auto& text(manager.addEntity());
				text.addComponent<TextComponent>(width + 100, height + 50, (screenW/2) - (width+100)/2, 100, 1, 1, color, "Game Over", renderer, Game::fontPtr);
				text.addGroup(Game::groupText);
				for (int i = 0; i < 3; i++) {
					auto& text(manager.addEntity());
					text.addComponent<TextComponent>(width, height, (screenW / 2) - (width) / 2, 150 + (i +1) * 30, 1, 1, color, stringArr[i], renderer, Game::fontPtr);
					text.addGroup(Game::groupText);
				}
				Game::alive = false;
			}
		}
		Vector2D pVel = newPlayer.getComponent<TransformComponent>().velocity;
		int pSpeed = newPlayer.getComponent<TransformComponent>().speed;
		for (auto t : tiles)
		{
			// scrolling tile map
			t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
			t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
		}
	}
	camera.h = 50 * 64 - 640;
	camera.w = 50 * 64 - 800;
	camera.x = playerPos.x - 400;
	camera.y = playerPos.y - 320;
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	Vector2D playerPos = newPlayer.getComponent<TransformComponent>().position;
	for (auto& t : tiles)
	{
		t->getComponent<TileComponent>().drawTile(newPlayer.getComponent<TransformComponent>().position.x, playerPos.y);
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& w : womens)
	{
		w->getComponent<SpriteComponent>().drawSprite(playerPos.x, playerPos.y);
	}
	for (auto& k : kids)
	{
		k->getComponent<SpriteComponent>().drawSprite(playerPos.x, playerPos.y);;
	}
	for (auto& c : colliders)
	{
		c->draw();
	}

	if (!Game::alive)
	{
		for (auto& tex : text)
		{
			tex->getComponent<TextComponent>().drawText();
		}
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	for (auto& w : womens)
	{
		w->destroy();
	}
	for (auto& k : kids)
	{
		k->destroy();
	}
	Game::cnt = 0;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}
void Game::quit()
{
	TTF_Quit();
	SDL_Quit();
}