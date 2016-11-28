#include "Vec2.h"
#include "Define.h"

#include "Inputs.h"
#include "Renderer.h"
#include "Audio.h"
#include "Gameplay.h"

#include "Character.h"
#include "Bullet.h"
#include "Static.h"
#include "Enemy.h"

void cleanUp();
inline bool InSight(const Vecf2 & a, const Vecf2& b);
inline float rand(float start, float stop);

int main(int, char**) {

	try {

		auto renderer = std::make_shared<Renderer>();
		auto audio = std::make_shared<Audio>();

		std::shared_ptr<Character> character;
		std::vector<std::shared_ptr<Bullet>> bullet_character_vector;
		std::vector<std::shared_ptr<Bullet>> bullet_enemy_vector;

		std::vector<std::shared_ptr<Static>> background_vector;
		std::vector<std::shared_ptr<Static>> second_plan_vector;
		std::vector<std::shared_ptr<Static>> first_plan_vector;

		std::vector<std::shared_ptr<Enemy>> enemy_vector;

		std::vector<std::vector<std::shared_ptr<Bullet>>::iterator> bullets_character_to_kill;
		std::vector<std::vector<std::shared_ptr<Bullet>>::iterator> bullets_enemy_to_kill;
		std::vector<std::vector<std::shared_ptr<Enemy>>::iterator> enemys_to_kill;

		//Load Map
		Map::Load("dev.csv", character, first_plan_vector, second_plan_vector, background_vector, renderer);

		//Statt music
//		audio->PlayMusic();

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
				character->Update(Gameplay::deltaTime, bullet_character_vector, audio);

				//Update bullets
				for (auto& bullet : bullet_character_vector) {
					bullet->Update(Gameplay::deltaTime);
				}

				for (auto& bullet : bullet_enemy_vector) {
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
//							enemy_vector.push_back(std::make_shared<Enemy>(Vecf2{ x,y }, "Enemy.png", renderer));
						}
					}
				}

				

				for (auto& enemy : enemy_vector) {
					enemy->Detect(character, bullet_enemy_vector);
					enemy->Update(Gameplay::deltaTime);
					if (enemy->position.y > 0.f ||
						enemy->position.y < -3000.f ||
						enemy->position.x > 3.f * abs(character->position.x + SCREEN_WIDTH) ||
						enemy->position.x < -3.f * abs(character->position.x - SCREEN_WIDTH)) enemy->life = false;
				}

				//Update background
				for (auto& background : background_vector) {


					if (abs(background->position.x - character->position.x) > 2*SCREEN_WIDTH) {
						if (background->position.x - character->position.x > 0) {
							background->position.x -= 4 * SCREEN_WIDTH;
						}
						else {
							background->position.x += 4 * SCREEN_WIDTH;
						}
					}

				}

				for (auto& second_plan : second_plan_vector) {

					second_plan->position.x += 40.f*Gameplay::deltaTime;

					if (abs(second_plan->position.x - character->position.x) > 2*SCREEN_WIDTH) {
						if (second_plan->position.x - character->position.x > 0) {
							second_plan->position.x -= 4 * SCREEN_WIDTH;
						}
						else {
							second_plan->position.x += 4 * SCREEN_WIDTH;
						}
					}
				}

				for (auto& first_plan : first_plan_vector) {

					first_plan->position.x += 20.f*Gameplay::deltaTime;

					if (abs(first_plan->position.x - character->position.x) > 2*SCREEN_WIDTH) {
						if (first_plan->position.x - character->position.x > 0) {
							first_plan->position.x -= 4 * SCREEN_WIDTH;
						}
						else {
							first_plan->position.x += 4 * SCREEN_WIDTH;
						}
					}
				}

			}

			//Collision
			//bullets & enemy & character
			for (auto& enemy : enemy_vector) {
				if (InSight(renderer->camera->position, enemy->position)) {

					character->Collison(enemy);

					for (auto& bullet : bullet_character_vector) {
						if (enemy->life) enemy->Collision(bullet);
					}
				}
			}

			//enemy bullets & character
			for (auto& bulltet : bullet_enemy_vector) {
				if (InSight(renderer->camera->position, bulltet->position)) {
					character->Collison(bulltet);
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
			for (auto& bullet : bullet_character_vector){
				if (bullet->life) bullet->Draw();
			}

			for (auto& bullet : bullet_enemy_vector) {
				if (bullet->life) bullet->Draw();
			}

	
			//Draw second plan
			for (auto& second_plan : second_plan_vector) {
				second_plan->Draw();
			}

			//Draw the player
			character->Draw();

			//Draw first plan
			for (auto& first_plan : first_plan_vector) {
				first_plan->Draw(false);
			}

			//Update the screen
			renderer->RenderPresent();

			//Killer zone
			//bullets
			for (std::vector<std::shared_ptr<Bullet>>::iterator it = bullet_character_vector.begin(); it != bullet_character_vector.end(); it++) {

				if (!it->get()->life) {
					bullets_character_to_kill.push_back(it);
				}
			}

			for (auto& obj : bullets_character_to_kill) {
				bullet_character_vector.erase(obj);
				break;
			}
			if(bullets_character_to_kill.size() > 0) bullets_character_to_kill.clear();

			for (std::vector<std::shared_ptr<Bullet>>::iterator it = bullet_enemy_vector.begin(); it != bullet_enemy_vector.end(); it++) {

				if (!it->get()->life) {
					bullets_enemy_to_kill.push_back(it);
				}
			}

			for (auto& obj : bullets_enemy_to_kill) {
				bullet_enemy_vector.erase(obj);
				break;
			}
			if (bullets_enemy_to_kill.size() > 0) bullets_enemy_to_kill.clear();

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
