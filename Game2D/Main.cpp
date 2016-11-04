#include "Vec2.h"
#include "Renderer.h"
#include "Define.h"
#include "Inputs.h"

#include "Character.h"
#include "Bullet.h"
#include "Static.h"
#include "Swarm.h"
#include "Gameplay.h"


void cleanUp();
inline bool InSight(const Vecf2 & a, const Vecf2& b);
inline float rand(float start, float stop);

int main(int, char**) {

	try {

		auto renderer = std::make_shared<Renderer>();

		std::shared_ptr<Character> character;
		std::vector<std::shared_ptr<Bullet>> bullet_vector;
		std::vector<std::shared_ptr<Static>> background_vector;
		std::vector<std::shared_ptr<Enemy>> enemy_vector;

		std::vector<std::vector<std::shared_ptr<Bullet>>::iterator> bullets_to_kill;
		std::vector<std::vector<std::shared_ptr<Enemy>>::iterator> enemys_to_kill;

		//Load Map
		Map::Load("dev.csv", character, background_vector, renderer);

		//Main loop
		bool quit = false;
		while (!quit) {

			quit = Inputs::Update();

			//Rendering
			renderer->Clear();

			//Get inputs
			character->Inputs();

			//Update Gameplay
			Gameplay::Update();

			if (!Gameplay::pausa) {
				//Update camera
				renderer->camera->MoveTo(character, Gameplay::deltaTime);

				//Update character
				character->Update(Gameplay::deltaTime, bullet_vector);

				//Update bullets
				for (auto& bullet : bullet_vector) {
					bullet->Update(Gameplay::deltaTime);
				}
				//Update enemy
				if (enemy_vector.size() < 50) {
					if (rand(0.f, 1.f) < 0.25f) {
						float angle = rand(0, 2 * PI);
						float x = character->position.x + SCREEN_WIDTH*sinf(angle);
						float y = character->position.y + SCREEN_WIDTH*cosf(angle);
						if (y < 0 &&
							y > -3000 ||
							x < 3 * (character->position.x + SCREEN_WIDTH) &&
							x > -3 * (character->position.x + SCREEN_WIDTH)) {
							enemy_vector.push_back(std::make_shared<Enemy>(Vecf2{ x,y }, "Enemy.png", renderer));
						}
					}
				}

				for (auto& enemy : enemy_vector) {
					enemy->Detect(character);
					enemy->Update(Gameplay::deltaTime);
					if (enemy->position.y > 0.f ||
						enemy->position.y < -3000.f ||
						enemy->position.x > 3.f * abs(character->position.x + SCREEN_WIDTH) ||
						enemy->position.x < -3.f * abs(character->position.x - SCREEN_WIDTH)) enemy->life = false;
				}

				//Update background
				for (auto& background : background_vector) {
					if (abs(background->position.x - character->position.x) > SCREEN_WIDTH) {
						if (background->position.x - character->position.x > 0) {
							background->position.x -= 2 * SCREEN_WIDTH;
						}
						else {
							background->position.x += 2 * SCREEN_WIDTH;
						}
					}
				}
			}

			//Collision
			//bullets & enemy & character
			for (auto& enemy : enemy_vector) {
				if (InSight(renderer->camera->position, enemy->position)) {

					character->Collison(enemy);

					for (auto& bullet : bullet_vector) {
						if (enemy->life) enemy->Collision(bullet);
					}
				}
			}

			//Draw the background
			for (auto& background : background_vector) {
				background->Draw();
			}

			//Draw the enemy
			for (auto& enemy : enemy_vector) {
				if(enemy->life) enemy->Draw();
			}

			//Draw the bullets
			for (auto& bullet : bullet_vector){
				if (bullet->life) bullet->Draw();
			}

			//Draw the player
			character->Draw();


			//Update the screen
			renderer->RenderPresent();

			//Killer zone
			//bullets
			for (std::vector<std::shared_ptr<Bullet>>::iterator it = bullet_vector.begin(); it != bullet_vector.end(); it++) {

				if (!it->get()->life) {
					bullets_to_kill.push_back(it);
				}
			}

			for (auto& obj : bullets_to_kill) {
				bullet_vector.erase(obj);
				break;
			}
			if(bullets_to_kill.size() > 0) bullets_to_kill.clear();

			//enemys
			for (std::vector<std::shared_ptr<Enemy>>::iterator it = enemy_vector.begin(); it != enemy_vector.end(); it++) {

				if (!it->get()->life) {
					enemys_to_kill.push_back(it);
				}

			}

			for (auto& obj : enemys_to_kill) {
				enemy_vector.erase(obj);
				break;
			}
			if (enemys_to_kill.size() > 0) enemys_to_kill.clear();


		}
	}
	catch (...) {
		cleanUp();
		printf("Shit!\n");
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

inline bool InSight(const Vecf2 & camera, const Vecf2& obj) {
	Vecf2 r{ obj.x - (camera.x + SCREEN_WIDTH / 2), camera.y - camera.y };
	return sqrt(r.x*r.x + r.y*r.y) < SCREEN_HEIGHT + 75;
}

inline float rand(float start, float stop) {
	return start+static_cast<float>(((stop - start)*rand()) / (RAND_MAX + 1.0));
}
