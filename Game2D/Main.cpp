#include "Renderer.h"

#include "Character.h"
#include "Swarm.h"
#include "Static.h"

#include "Vec2.h"

#include "Define.h"
#include "Camera.h"
#include "Inputs.h"

void cleanUp();

int main(int, char**) {

	try {
		
		auto renderer = std::make_shared<Renderer>();

		// Init player
		std::shared_ptr<Character> player;

		std::shared_ptr<Swarm> swarm;

		std::vector<std::shared_ptr<Static>> floorVect;
		std::shared_ptr<Static> background;

		//Load Map
		Map::load("level1.csv", player, swarm, floorVect, background, renderer);

		//Init camera
		auto camera = std::make_shared<Camera>(player->position, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT));

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
			renderer->Clear();

			//Update player
			deltaTime = (nowTime - lastTime) / 1000;
			lastTime = nowTime;

			player->Inputs();

			//Collisios
			for (auto floor : floorVect) {
				player->Collison(floor);
			}

			player->Update(deltaTime);

			swarm->Update(deltaTime);

			background->position.x = (player->position.x - 1000.f) * 0.3f;

			//Draw backgrounde
			renderer->render(background, camera);

			//Draw the player
			renderer->render(player, camera);

			//Draw the Enemy
			for (auto& enemy : swarm->swarm) {
				renderer->render(enemy, camera);
			}

			for (auto& floor : floorVect) {
				renderer->render(floor, camera);
			}

			//Update the screen
			renderer->RenderPresent();
		}
	} catch (...) {
		cleanUp();
		system("pause");
		return 1;
	}

	//Clean up
	cleanUp();

	return 0;
}

void cleanUp() {
	IMG_Quit();
	SDL_Quit();
}