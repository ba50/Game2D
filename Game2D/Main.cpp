#include <string>
#include <iostream>
#include <memory>

#include <SDL.h>
#include <SDL_image.h>

#include "Object.h"
#include "cleanup.h"

int main(int, char**) {

	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		StaticMath::logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	//Setup our window and renderer
	SDL_Window *window = SDL_CreateWindow("Lesson 5", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		StaticMath::logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		StaticMath::logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	//iW and iH are the clip width and height
	//We'll be drawing only clips so get a center position for the w/h of a clip
	float x = SCREEN_WIDTH / 2 - 50;
	float y = SCREEN_HEIGHT / 2 - 50;

	std::shared_ptr<Object> obj = std::make_shared<Object>(x, y, "image.png", renderer);
	if (obj->sprite == nullptr) {
		cleanup(renderer, window);
		IMG_Quit();
		SDL_Quit();

		return 1;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	float now;
	float last = 0.f;
	SDL_Event e;
	bool quit = false;
	while (!quit) {

		now = static_cast<float>(SDL_GetTicks());

		//Event Polling
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			//Use number input to select which clip should be drawn
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_UP:
					obj->useClip = 0;
					obj->momentum.y -= 500;
					break;
				case SDLK_DOWN:
					obj->useClip = 1;
					obj->momentum.y += 500;
					break;
				case SDLK_RIGHT:
					obj->useClip = 2;
					obj->momentum.x += 500;
					break;
				case SDLK_LEFT:
					obj->useClip = 3;
					obj->momentum.x -= 500;
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
			}
		}

		obj->Update((now - last) / 1000);
		last = now;

		//Rendering
		SDL_RenderClear(renderer);

		//Draw the image
		StaticMath::renderTexture(obj->sprite, renderer, static_cast<int>(obj->pos.x), static_cast<int>(obj->pos.y), &obj->clips[obj->useClip]);

		//Update the screen
		SDL_RenderPresent(renderer);
	}

	//Clean up
	cleanup(renderer, window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}