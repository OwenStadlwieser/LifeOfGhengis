
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
Game::Game()
{}

Game::~Game()
{}


void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	std::cout << "Welcome to the life of Ghengis" << std::endl;
	std::cout << "The goal of the game is to create a swarm by interacting with the women in the red shirt" << std::endl;
	std::cout << "Unfortunately your swarm does not like you and will attempt to kill you" << std::endl;
	std::cout << "Use WASD for controls, press P to play" << std::endl;
	std::cout << "Press 'esc' to quit" <<  std::endl;
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
			std::cout << "Sett" << std::endl;
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
			k->getComponent<KidMovementComponent>().updatevelocity(newPlayer.getComponent<TransformComponent>().position.x - 20 * Game::cnt / 2 + 20 * i + rand() % (30 + 1 - 30) - 30,
				newPlayer.getComponent<TransformComponent>().position.y - 20 * Game::cnt / 2 + 20 * i + rand() % (30 + 1 - 30) - 30);
			i++;
			SDL_Rect kCol = k->getComponent<ColliderComponent>().collider;
			if (Collision::KP(kCol, playerCol))
			{
				std::cout << "Game Over" << std::endl;
				std::cout << "You created a swarm of " << Game::cnt  << std::endl;
				std::cout << "Press P to play again" << std::endl;
				Game::alive = false;
			}
		}
		camera.h = 50 * 64 - 640;
		camera.w = 50 * 64 - 800;
		camera.x = newPlayer.getComponent<TransformComponent>().position.x - 400;
		camera.y = newPlayer.getComponent<TransformComponent>().position.y - 320;
		if (camera.x < 0)
			camera.x = 0;
		if (camera.y < 0)
			camera.y = 0;
		if (camera.x > camera.w)
			camera.x = camera.w;
		if (camera.y > camera.h)
			camera.y = camera.h;
		Vector2D pVel = newPlayer.getComponent<TransformComponent>().velocity;
		int pSpeed = newPlayer.getComponent<TransformComponent>().speed;
		for (auto t : tiles)
		{
			// scrolling tile map
			t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
			t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->getComponent<TileComponent>().drawTile(newPlayer.getComponent<TransformComponent>().position.x, newPlayer.getComponent<TransformComponent>().position.y);
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& w : womens)
	{
		w->getComponent<SpriteComponent>().drawSprite(newPlayer.getComponent<TransformComponent>().position.x, newPlayer.getComponent<TransformComponent>().position.y);
	}
	for (auto& k : kids)
	{
		k->getComponent<SpriteComponent>().drawSprite(newPlayer.getComponent<TransformComponent>().position.x, newPlayer.getComponent<TransformComponent>().position.y);;
	}
	for (auto& c : colliders)
	{
		c->draw();
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
	SDL_Quit();
}