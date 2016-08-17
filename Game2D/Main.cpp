#include <memory>

#include "Object.h"
#include "Inputs.h"
#include "cleanup.h"

void cleanUp(SDL_Renderer *renderer, SDL_Window *window);

int main(int, char**) {

	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	try {
		//Start up SDL and make sure it went ok
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			StaticMath::logSDLError(std::cout, "SDL_Init");
			return 1;
		}

		//Setup our window and renderer
		window = SDL_CreateWindow("Lesson 5", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			StaticMath::logSDLError(std::cout, "CreateWindow");
			SDL_Quit();
			return 1;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr) {
			StaticMath::logSDLError(std::cout, "CreateRenderer");
			cleanup(window);
			SDL_Quit();
			return 1;
		}

		float x = SCREEN_WIDTH / 2;
		float y = SCREEN_HEIGHT / 2;

		std::vector<std::shared_ptr<Object>> objVec;
		objVec.push_back(std::make_shared<Object>(x + 100, y - 50, "image.png", renderer));
		objVec.push_back(std::make_shared<Object>(x - 150, y - 50, "image.png", renderer));

		// std::tuple< bool, Renderer&, Window* >
		// std::tie( success, renderer, window ) = init();

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		float lastTime = 0.f;
		float DeltaTime;
		float nowTime;
		bool quit = false;
		while (!quit) {

			nowTime = static_cast<float>(SDL_GetTicks());
			
			quit = Inputs::Update(objVec[0].get());

//			for (size_t i = 0; i < Inputs::events.size();i++) {
//				Inputs::events.pop_back();
//			}

			DeltaTime = (nowTime - lastTime);
			for (auto& obj : objVec) {
				obj.get()->Update(DeltaTime);
			}
			lastTime = nowTime;

			//Rendering
			SDL_RenderClear(renderer);

			//Draw the image
			for (auto& obj : objVec) {
				Texture::render(obj.get()->sprite, renderer, static_cast<int>(obj.get()->pos.x), static_cast<int>(obj.get()->pos.y), &obj.get()->clips[obj.get()->useClip]);
			}

			for (size_t i = 0; i < objVec.size(); i++) {
				for (size_t j = i; j < objVec.size(); j++) {
					if (i != j) {
						if (StaticMath::collison(objVec[i].get(), objVec[j].get())) {

							Object::Collision(objVec[i].get()->momentum, objVec[j].get()->momentum);

						}
					}
				}
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