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
#include "Gameplay.h"

#include "Character.h"
#include "Static.h"

#define PI 3.1416f
#define g 9.81f 

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
		throw std::exception("Nooo!");
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

namespace Map {
	static void Load(

		const std::string &file,
		std::shared_ptr<Character> &player,
		std::vector<std::shared_ptr<Static>> &first_plan_vector,
		std::vector<std::shared_ptr<Static>> &secodn_plan_vector,
		std::vector<std::shared_ptr<Static>> &background_vector,
		std::shared_ptr<Renderer> &ren

	) {

		std::vector<SDL_Rect> cloud_clips;

		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 5; j++) {
				cloud_clips.push_back(SDL_Rect{ i * 143,j * 86, 143, 86 });
			}
		}

		std::vector<SDL_Rect> player_clips;
		for (int i = 0; i < 35;  i++) {
			player_clips.push_back(SDL_Rect{ i*BLOCK_SIZE, 0,BLOCK_SIZE,BLOCK_SIZE });
		}

		std::vector<SDL_Rect> bg_clips;
		bg_clips.push_back(SDL_Rect{ 0,0,1280,3000 });

		std::vector<SDL_Rect> water_clips;
		water_clips.push_back(SDL_Rect{ 0,0,1280,640 });

		std::vector<SDL_Rect> sky_clips;
		sky_clips.push_back(SDL_Rect{ 0,0,1280,250 });

		Gameplay::water_level = 0.f;
		Gameplay::sky_level = -static_cast<float>(bg_clips[0].h)*Renderer::scale.y;

		std::ifstream in;
		in.open(file);
		std::string buffer;
		float x = 0, y = 0;
		while (!in.eof()) {
			in >> buffer;
			for (auto& c : buffer) {
				if (c == '@') {
					player = std::make_shared<Character>(Vecf2{ x, y }, "Source/MyChar.png", player_clips, *ren);
					ren->camera->position = Vecf2{ x - SCREEN_WIDTH / 2.f,y - SCREEN_HEIGHT / 2.f };

					for (float i = -2; i < 3; i++) {
						background_vector.push_back(
							std::make_shared<Static>(
								Vecf2{ i * (float)bg_clips[0].w*Renderer::scale.x + x,
								Gameplay::sky_level / 2.f },
								"Source/BG.png",
								bg_clips,
								*ren));
					}

					for (float i = -2; i < 3; i++) {
						first_plan_vector.push_back(
							std::make_shared<Static>(
								Vecf2{ i * (float)water_clips[0].w*Renderer::scale.x + x,
								Gameplay::water_level + static_cast<float>(water_clips[0].h)*Renderer::scale.y / 2.f },
								"Source/Water.png",
								water_clips,
								*ren));
					}

		/*			for (float i = -2; i < 3; i++) {
						first_plan_vector.push_back(
							std::make_shared<Static>(
								Vecf2{ i * (float)sky_clips[0].w*Renderer::scale.x,
								Gameplay::sky_level },
								"Source/Sky.png",
								sky_clips,
								*ren));
					}*/
					
				}

				x += 5 * BLOCK_SIZE*Renderer::scale.x;

				if (c == 'c') {
					for (float i = -2; i < 3; i++) {
						secodn_plan_vector.push_back(
							std::make_shared<Static>(
								Vecf2{ i * SCREEN_WIDTH + x,
								y },
								"Source/CloudSprites.png",
								cloud_clips,
								*ren));
					}
				}

			}

			y -= 5 * BLOCK_SIZE*Renderer::scale.y;
			x = 0;

		}

		float i = 100;
		float z, scale;
		for (auto& obj : secodn_plan_vector) {
			z = i / (float)secodn_plan_vector.size();
			obj->useClip = static_cast<int>(floorf(Math::Rand(0.f, 34.f)));
			obj->velocity.x = 5.f*z;
			obj->velocity.y = 15.f*z;
			scale = 2.f*z*floorf(Math::Rand(1.f, 4.f));
			obj->scale = Vecf2{ scale, scale };
			i+=1.5f;
		}

	}

}
