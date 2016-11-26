#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>

#include "Renderer.h"
#include "Camera.h"

#include "Character.h"
#include "Static.h"

#define PI 3.1416f
#define g 9.81f 

//Screen attributes
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define BLOCK_SIZE 32
#define SKY_LEVEL -3000
#define WATER_LEVEL 0

namespace Error
{
	/*
	* Log an SDL error with some error message to the output stream of our choice
	* @param os The output stream to write the message too
	* @param msg The error message to write, format will be msg error: SDL_GetError()
	*/
	static void LogSDL(std::ostream &os, const std::string &msg)
	{
		os << msg << " error: " << SDL_GetError() << std::endl;
		throw std::exception("shit!");
	}
}

namespace Map {
	static void Load(const std::string &file, std::shared_ptr<Character> &player,
		std::vector<std::shared_ptr<Static>> &first_plan_vector,
		std::vector<std::shared_ptr<Static>> &secodn_plan_vector,
		std::vector<std::shared_ptr<Static>> &background_vector,
		std::shared_ptr<Renderer> ren) {

		std::ifstream in;
		in.open(file);
		std::string buffer;
		float x = 0, y = 0;
		while (!in.eof()) {
			in >> buffer;
			for (auto& c : buffer) {
				if (c != ';') {
					if (c == '@') {
						player = std::make_shared<Character>(Vecf2{ x, y }, "MyChar.png", ren);
						ren->camera->position = Vecf2{ x - SCREEN_WIDTH / 2.f,y - SCREEN_HEIGHT / 2.f };

					background_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ -2*SCREEN_WIDTH, -1500, SCREEN_WIDTH, 3000 }, "BG.png", ren));
						background_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ -SCREEN_WIDTH, -1500, SCREEN_WIDTH, 3000 }, "BG.png", ren));
						background_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ 0 ,-1500,  SCREEN_WIDTH,  3000 }, "BG.png", ren));
						background_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ SCREEN_WIDTH, -1500,  SCREEN_WIDTH,  3000 }, "BG.png", ren));
						background_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ 2*SCREEN_WIDTH, -1500,  SCREEN_WIDTH,  3000 }, "BG.png", ren));

						first_plan_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ -2*SCREEN_WIDTH, WATER_LEVEL+300,  SCREEN_WIDTH,  640 }, "Water.png", ren));
						first_plan_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ -SCREEN_WIDTH, WATER_LEVEL+300,  SCREEN_WIDTH,  640 }, "Water.png", ren));
						first_plan_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ 0, WATER_LEVEL+300,  SCREEN_WIDTH,  640 }, "Water.png", ren));
						first_plan_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ SCREEN_WIDTH, WATER_LEVEL+300,  SCREEN_WIDTH,  640 }, "Water.png", ren));
						first_plan_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ 2*SCREEN_WIDTH, WATER_LEVEL+300,  SCREEN_WIDTH,  640 }, "Water.png", ren));

						first_plan_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ -2*SCREEN_WIDTH, SKY_LEVEL,  SCREEN_WIDTH,  250 }, "Sky.png", ren));
						first_plan_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ -SCREEN_WIDTH, SKY_LEVEL,  SCREEN_WIDTH,  250 }, "Sky.png", ren));
						first_plan_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ 0, SKY_LEVEL,  SCREEN_WIDTH,  250 }, "Sky.png", ren));
						first_plan_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ SCREEN_WIDTH, SKY_LEVEL,  SCREEN_WIDTH,  250 }, "Sky.png", ren));
						first_plan_vector.push_back(
							std::make_shared<Static>(SDL_Rect{ 2*SCREEN_WIDTH, SKY_LEVEL,  SCREEN_WIDTH,  250 }, "Sky.png", ren));
					}
					x += 10*BLOCK_SIZE;
				}
				if (c == 'c') {
					secodn_plan_vector.push_back(std::make_shared<Static>(SDL_Rect{ static_cast<int>(x), static_cast<int>(y),  331,  183 }, "Clouds.png", ren));
				}
			}
			y -= 10*BLOCK_SIZE;
			x = 0;
		}
	}

}

namespace Math {
	template <typename T> int Sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

	inline float Rand(float start, float stop) {
		return start + static_cast<float>(((stop - start)*rand()) / (RAND_MAX + 1.0));
	}
}