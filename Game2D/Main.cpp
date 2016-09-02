#include <memory>

#include "Character.h"
#include "Static.h"
#include "Vec2.h"
#include "Define.h"
#include "Camera.h"

#include "cleanup.h"

void cleanUp(SDL_Renderer *renderer, SDL_Window *window);
std::tuple<SDL_Window*, SDL_Renderer*> init();

int main(int, char**) {

	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	try {

		std::tie(window, renderer) = init();

		//Init camera
		auto camera = std::make_shared<Camera>(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT));

		// Init player
		std::shared_ptr<Character> player;
		std::vector<std::shared_ptr<Static>> floorVect;

		//Load Map
		Map::load("level1.csv", player, floorVect, renderer);

		//Set background color
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		//Set time counter
		float lastTime = 0.f;
		float deltaTime;
		float nowTime;

		//Main loop
		bool quit = false;
		while (!quit) {
			nowTime = static_cast<float>(SDL_GetTicks());
			
			quit = Inputs::Update();

			camera->MoveTo(player->position);

			//Rendering
			SDL_RenderClear(renderer);

			//Update player
			deltaTime = (nowTime - lastTime) / 1000;
			lastTime = nowTime;

			player->Inputs();

			//Collisios
			for (auto floor : floorVect) {
				player->Collison(floor);
			}


			player.get()->Update(deltaTime);

			//Draw the player
			Texture::render(player.get()->sprite, renderer, player, camera);

			for (auto& floor : floorVect) {
				Texture::render(floor.get()->sprite, renderer, floor, camera);
			}

			//Update the screen
			SDL_RenderPresent(renderer);
		}
	} catch (...) {
		cleanUp(renderer, window);
		return 1;
	}

	//Clean up
	cleanUp(renderer, window);

	return 0;
}

void cleanUp(SDL_Renderer *renderer, SDL_Window *window) {
	cleanup(renderer, window);
	IMG_Quit();
	SDL_Quit();
}

std::tuple<SDL_Window*, SDL_Renderer*> init() {
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		Error::logSDL(std::cout, "SDL_Init");
	}

	//Setup our window and renderer
	SDL_Window *window = SDL_CreateWindow("Game 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		Error::logSDL(std::cout, "CreateWindow");
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		Error::logSDL(std::cout, "CreateRenderer");
	}

	return std::make_tuple(window, renderer);
}