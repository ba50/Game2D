#include "Vec2.h"
#include "Renderer.h"
#include "Define.h"
#include "Inputs.h"

#include "Character.h"
#include "Bullet.h"
#include "Static.h"
#include "Swarm.h"

void cleanUp();
inline bool InSight(const Vecf2 & a, const Vecf2& b);
inline float rand(float start, float stop);

int main(int, char**) {

	try {

		auto renderer = std::make_shared<Renderer>();

		std::shared_ptr<Character> character;
		std::vector<std::shared_ptr<Bullet>> bullet_vector;
		std::vector<std::shared_ptr<Static>> background_vector;

		std::vector<std::vector<std::shared_ptr<Bullet>>::iterator> bullets_to_kill;

		//Load Map
		Map::Load("dev.csv", character, background_vector, renderer);

		//Set time counter
		float lastTime = 0.f;
		float deltaTime ( 0.f);
		float nowTime { 0.f };

		//Main loop
		bool quit = false;
		while (!quit) {
			nowTime = static_cast<float>(SDL_GetTicks());

			quit = Inputs::Update();

			//Rendering
			renderer->Clear();

			deltaTime = (nowTime - lastTime) / 1000.f;
			lastTime = nowTime;

			character->Inputs();

			renderer->camera->MoveTo(character, deltaTime);

			//Update character
			character->Update(deltaTime, bullet_vector);

			//Update bullets
			for (auto& bullet : bullet_vector) {
				bullet->Update(deltaTime);
			}

			//Update background
			for (auto& background : background_vector) {
				if (abs(background->position.x - character->position.x) > SCREEN_WIDTH) {
					if (background->position.x - character->position.x > 0) {
						background->position.x -= 2 * SCREEN_WIDTH;
					}
					else{
						background->position.x += 2 * SCREEN_WIDTH;
					}
				}
			}


			//End of game?
			if (!character->life) {
				throw std::exception("Shit!");
			}

			//Draw the background
			for (auto& background : background_vector) {
				background->Draw();
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
			for (std::vector<std::shared_ptr<Bullet>>::iterator it = bullet_vector.begin(); it != bullet_vector.end(); it++) {

				if (!it->get()->life) {
					bullets_to_kill.push_back(it);
				}
			}

			for (auto& obj : bullets_to_kill) {
				bullet_vector.erase(obj);
			}
			if(bullets_to_kill.size() != 0) bullets_to_kill.clear();
			
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

inline bool InSight(const Vecf2 & a, const Vecf2& b) {
	Vecf2 r{ a.x - (b.x + SCREEN_WIDTH / 2), a.y - b.y };
	return sqrt(r.x*r.x + r.y*r.y) < SCREEN_HEIGHT + 75;
}

inline float rand(float start, float stop) {
	return start+static_cast<float>(((stop - start)*rand()) / (RAND_MAX + 1.0));
}
