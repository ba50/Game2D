#include "Vec2.h"

#include "Inputs.h"
#include "Renderer.h"
#include "Audio.h"
#include "Gameplay.h"

#include "Character.h"
#include "Bullet.h"
#include "Static.h"
#include "Enemy.h"

#include <random>

void cleanUp();
inline bool InSight(const Vecf2 & a, const Vecf2& b);

int main(int, char**) {
	
	try {

		auto renderer = std::make_shared<Renderer>();
//		auto audio = std::make_shared<Audio>();

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
		Map::Load("Source/dev.csv", character, first_plan_vector, second_plan_vector, background_vector, renderer);

		std::vector<SDL_Rect> bullet_clips;
		bullet_clips.push_back(SDL_Rect{ 0,0,BLOCK_SIZE / 2,BLOCK_SIZE / 2 });
		bullet_clips.push_back(SDL_Rect{ BLOCK_SIZE,0,BLOCK_SIZE / 2,BLOCK_SIZE / 2 });

		std::vector<SDL_Rect> enemy_clips;
		enemy_clips.push_back(SDL_Rect{ 0, 0, BLOCK_SIZE, BLOCK_SIZE });
		enemy_clips.push_back(SDL_Rect{ BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE });
		enemy_clips.push_back(SDL_Rect{ 0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE });
		enemy_clips.push_back(SDL_Rect{ BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE });
		//Statt music
//		audio->PlayMusic();

		//Random
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(0, 1);

		Inputs::slope.push_back(false);
		Inputs::slope.push_back(false);

		//Main loop
		bool quit = false;
		while (!quit) {
			Inputs::Update(quit);
			//Rendering
			renderer->Clear();

			//Get inputs
			character->Inputs();

			//Update Gameplay
			Gameplay::Update();

			//Update character
			character->Update(Gameplay::deltaTime);

			if (!Gameplay::pausa) {
				//Update camera
				renderer->camera->MoveTo(character, Gameplay::deltaTime);

				if (character->shoot) {
					Vecf2 position_temp{
						character->position.x + 1.1f*BLOCK_SIZE*sin(character->angle*PI / 180.f),
						character->position.y - 1.1f*BLOCK_SIZE*cos(character->angle*PI / 180.f)
					};
					bullet_character_vector.push_back(
						std::make_shared<Bullet>(
							character->velocity,
							character->angle + Math::Rand(-character->recoil, character->recoil),
							position_temp,
							"Source/Bullet.png",
							bullet_clips,
							*renderer,
							Vecf2{ 0.5f, 0.5f }));

					//audio->PlayExplosion();
					character->shoot = false;
				}

				//Update bullets
				for (auto& bullet : bullet_character_vector) {
					bullet->Update(Gameplay::deltaTime);
				}

				for (auto& bullet : bullet_enemy_vector) {
					bullet->Update(Gameplay::deltaTime);
				}

				//Update enemy
				if (enemy_vector.size() < 50) {
					if (dis(gen) < 0.25f) {
						float angle = dis(gen) * 2 * PI;
						float x = character->position.x + SCREEN_WIDTH*sin(angle);
						float y = character->position.y + SCREEN_WIDTH*cos(angle);
						if (y < Gameplay::water_level &&
							y > Gameplay::sky_level ||
							x < 3 * (character->position.x + SCREEN_WIDTH) &&
							x > -3 * (character->position.x + SCREEN_WIDTH)) {
							enemy_vector.push_back(
								std::make_shared<Enemy>(
									Vecf2{ x,y },
									"Source/Enemy.png",
									enemy_clips,
									*renderer
									));
						}
					}
				}

				for (auto& enemy : enemy_vector) {
					enemy->Detect(*character);
					enemy->Update(Gameplay::deltaTime);
					if (enemy->shoot) {
						Vecf2 position_temp{
							enemy->position.x + 1.1f*BLOCK_SIZE*sin(enemy->angle*PI / 180.f),
							enemy->position.y - 1.1f*BLOCK_SIZE*cos(enemy->angle*PI / 180.f)
						};
						bullet_enemy_vector.push_back(
							std::make_shared<Bullet>(
								enemy->velocity,
								enemy->angle + Math::Rand(-5.f, 5.f),
								position_temp,
								"Source/Bullet.png",
								bullet_clips,
								*renderer));

						//			audio->PlayExplosion();
						enemy->shoot = false;
					}
					if (enemy->position.y > 0.f ||
						enemy->position.y < -3000.f ||
						enemy->position.x > 3.f * abs(character->position.x + SCREEN_WIDTH) ||
						enemy->position.x < -3.f * abs(character->position.x - SCREEN_WIDTH)) enemy->life = false;
				}

				//Collision
				//bullets & enemy & character
				for (auto& enemy : enemy_vector) {
					if (InSight(renderer->camera->position, enemy->position)) {

						character->Collison(*enemy);

						for (auto& bullet : bullet_character_vector) {
							if (enemy->life) enemy->Collision(bullet);
						}
						for (auto& oth : enemy_vector) {
							if (enemy != oth) {
								enemy->Collision(*oth);
							}
						}
					}
				}

				//enemy bullets & character
				for (auto& bulltet : bullet_enemy_vector) {
					if (InSight(renderer->camera->position, bulltet->position)) {
						character->Collison(*bulltet);
					}
				}

			}

			//Update background
			for (auto& background : background_vector) {

				if (abs(background->position.x - character->position.x) > 2 * background->width*Renderer::scale.x) {
					if (background->position.x - character->position.x > 0) {
						background->position.x -= 4 * background->width*Renderer::scale.x;
					}
					else {
						background->position.x += 4 * background->width*Renderer::scale.x;
					}
				}

			}

			for (auto& second_plan : second_plan_vector) {

				second_plan->Update(Gameplay::deltaTime);
				second_plan->position.x -= .001f*character->velocity.x*second_plan->velocity.x;
				second_plan->position.y -= .0001f*character->velocity.y*second_plan->velocity.y;

				if (abs(second_plan->position.x - character->position.x) > 2 * SCREEN_WIDTH) {
					if (second_plan->position.x - character->position.x > 0) {
						second_plan->position.x -= 4 * SCREEN_WIDTH;
					}
					else {
						second_plan->position.x += 4 * SCREEN_WIDTH;
					}
				}
			}

			int i = 0;
			for (float x = -2; x < 3; x++) {
				first_plan_vector[i]->position.x
					= character->position.x - x *first_plan_vector[i]->width*Renderer::scale.x;
				i++;
			}

			for (auto& first_plan : first_plan_vector) {

				first_plan->position.x += 20.f*Gameplay::deltaTime;

				if (abs(first_plan->position.x - character->position.x) > 2 * SCREEN_WIDTH) {
					if (first_plan->position.x - character->position.x > 0) {
						first_plan->position.x -= 4 * first_plan->width*Renderer::scale.x;
					}
					else {
						first_plan->position.x += 4 * first_plan->width*Renderer::scale.x;
					}
				}
			}


			//Draw the background
			for (auto& background : background_vector) {
				renderer->Render(*background);
			}
	
			//Draw second plan
			for (auto& second_plan : second_plan_vector) {
				renderer->Render(*second_plan);
			}

			//Draw the enemy
			for (auto& enemy : enemy_vector) {
				if (enemy->life) renderer->Render(*enemy);
			}

			//Draw the bullets
			for (auto& bullet : bullet_character_vector){
				if (bullet->life) renderer->Render(*bullet);
			}

			for (auto& bullet : bullet_enemy_vector) {
				if (bullet->life) renderer->Render(*bullet);
			}

			//Draw the player
			renderer->Render(*character);
			renderer->Render(*character->engine, character->engine->angle);

			//Draw first plan
			for (auto& first_plan : first_plan_vector) {
				renderer->Render(*first_plan, 0, false);
			}

			SDL_SetRenderDrawColor(renderer->ren, 255, 0, 0, -(character->health-255));
			SDL_SetRenderDrawBlendMode(renderer->ren, SDL_BLENDMODE_BLEND);
			SDL_Rect life = SDL_Rect{ 0, 0,SCREEN_WIDTH,SCREEN_HEIGHT };
			SDL_RenderFillRect(renderer->ren, &life);

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
		std::cout << "Ooo nooo!\n";

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
