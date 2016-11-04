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

		std::shared_ptr<Character> player;

		//Load Map
		Map::Load("dev.csv", player, renderer);

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

			player->Inputs();

			renderer->camera->MoveTo(player, deltaTime);

			player->Update(deltaTime);

			if (!player->life) {
				throw std::exception("Shit!");
			}

			//Draw the player
			player->Draw();

			//Update the screen
			renderer->RenderPresent();
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
