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

		std::vector<std::shared_ptr<Swarm>> swarmVect;

		std::vector<std::shared_ptr<Static>> floorVect;
		std::shared_ptr<Static> background;

		//Load Map
		Map::load("level1.csv", player, swarmVect, floorVect, background, renderer);

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

			for (auto& swarm : swarmVect) {
				Vecf2 r{ swarm->position.x - (camera->position.x + SCREEN_WIDTH / 2), swarm->position.y - camera->position.y };
				if (sqrt(r.x*r.x + r.y*r.y) < SCREEN_HEIGHT) {
					swarm->Detect(player);
				}
			}

			//Collisios
			for (auto& floor : floorVect) {
				Vecf2 r{ floor->position.x - (camera->position.x + SCREEN_WIDTH / 2), floor->position.y - camera->position.y };
				if (sqrt(r.x*r.x + r.y*r.y) < SCREEN_HEIGHT) {
						player->Collison(floor);
						for (auto& swarm : swarmVect) {
							for (auto& enemy : swarm->swarm) {
								enemy->Collision(floor);
							}
						}
					}
			}

			player->Update(deltaTime);

			for (auto& swarm : swarmVect) {
				Vecf2 r{ swarm->position.x - (camera->position.x + SCREEN_WIDTH / 2), swarm->position.y - camera->position.y };
				if (sqrt(r.x*r.x + r.y*r.y) < SCREEN_HEIGHT) {
					swarm->Update(deltaTime);
				}
			}

			background->position.x = player->position.x * 0.3f;

			//Draw backgrounde
			renderer->render(background, camera);

			//Draw the player
			renderer->render(player, camera);

			//Draw the Enemy
			for (auto& swarm : swarmVect) {
				Vecf2 r{ swarm->position.x - (camera->position.x + SCREEN_WIDTH / 2), swarm->position.y - camera->position.y };
				if (sqrt(r.x*r.x + r.y*r.y) < SCREEN_HEIGHT) {
					for (auto& enemy : swarm->swarm) {
						renderer->render(enemy, camera);
					}
				}
			}

			for (auto& floor : floorVect) {

				Vecf2 r{ floor->position.x - (camera->position.x+SCREEN_WIDTH/2), floor->position.y - camera->position.y };
				if (sqrt(r.x*r.x + r.y*r.y) < SCREEN_HEIGHT) {
					renderer->render(floor, camera);
				}

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