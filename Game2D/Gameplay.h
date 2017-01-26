#pragma once

#include <chrono>
#include <thread>

struct Gameplay {
	static float deltaTime;
	
	static unsigned timer;

	static bool pausa;
	static bool slow_motion;
	static bool score;
	static bool start;

	static float sky_level;
	static float water_level;


	static void Update() {

		if (slow_motion) {
			if (timer > 25) {
				slow_motion = false;
				timer = 0;
			}
			deltaTime = 1.1e-2f;
			timer++;
		}
		else {
			deltaTime = 2e-2f;
		}

		if (score) {
			std::this_thread::sleep_for(std::chrono::milliseconds(25));
			score = false;
		}
	}

};
