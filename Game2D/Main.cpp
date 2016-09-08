#include "Vec2.h"
#include "Renderer.h"
#include "Define.h"
#include "Inputs.h"

#include "Character.h"
#include "Static.h"
#include "Swarm.h"

void cleanUp();
inline bool InSight(const Vecf2 & a, const Vecf2& b);
inline float rand(float start, float stop);

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

		//Set time counter
		float lastTime = 0.f;
		float deltaTime;
		float nowTime;

		//Main loop
		bool quit = false;
		while (!quit) {
			nowTime = static_cast<float>(SDL_GetTicks());

			quit = Inputs::Update();

			//Rendering
			renderer->Clear();

			//Update player
			deltaTime = (nowTime - lastTime) / 1000;
			lastTime = nowTime;

			player->Inputs();

			for (auto& swarm : swarmVect) {
				if (InSight(swarm->position, renderer->camera->position)) {
					swarm->Detect(player);
				}
			}

			//Collisios
			for (auto& floor : floorVect) {
				if (InSight(floor->position, renderer->camera->position)) {
					player->Collison(floor);
					for (auto& swarm : swarmVect) {
						if (InSight(swarm->position, renderer->camera->position)) {
							for (auto& enemy : swarm->enemyList) {
								enemy->Collision(floor);
							}
						}
					}
				}
			}

			for (auto& swarm : swarmVect) {
				if (InSight(swarm->position, renderer->camera->position)) {
					for (auto& enemy : swarm->enemyList) {
						for (auto& bullet : player->bulletList) {
							enemy->Collision(bullet);
						}
					}
				}
			}

			renderer->camera->MoveTo(player, deltaTime);

			player->Update(deltaTime);

			for (auto& swarm : swarmVect) {
				if (InSight(swarm->position, renderer->camera->position)) {
					swarm->Update(deltaTime);
				}
			}

			background->position.x = player->position.x * 0.3f;

			//Draw backgrounde
			background->Draw();

			//Draw the player
			player->Draw();


			//Draw the Enemy
			for (auto& swarm : swarmVect) {
				if (InSight(swarm->position, renderer->camera->position)) {
					swarm->Draw();
				}
			}

			//Draw floor
			for (auto& floor : floorVect) {
				if (InSight(floor->position, renderer->camera->position)) {
					floor->Draw();
				}
			}

			//Update the screen
			renderer->RenderPresent();
		}
	}
	catch (...) {
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

inline bool InSight(const Vecf2 & a, const Vecf2& b) {
	Vecf2 r{ a.x - (b.x + SCREEN_WIDTH / 2), a.y - b.y };
	return sqrt(r.x*r.x + r.y*r.y) < SCREEN_HEIGHT + 75;

}

inline float rand(float start, float stop) {
	return start+static_cast<float>(((stop - start)*rand()) / (RAND_MAX + 1.0));
}
