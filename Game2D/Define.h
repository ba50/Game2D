#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <random>

#include <SDL.h>
#include <SDL_image.h>

#include "Renderer.h"
#include "Camera.h"

#include "Character.h"
#include "Static.h"
#include "Swarm.h"

#define PI 3.1416f
#define g 9.81f 

//Screen attributes
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define BLOCK_SIZE 32

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
	static void Load(const std::string &file, std::shared_ptr<Character> &player, std::shared_ptr<Renderer> ren) {

		std::ifstream in;
		in.open(file);
		std::string buffer;
		float x = 0, y = 0;
		while (!in.eof()) {
			in >> buffer;
			for (auto& c : buffer) {
				if (c != ';') {
					if (c == '@') {
						player = std::make_shared<Character>(x, y, "MyChar.png", ren);
						ren->camera->position = Vecf2{ x-SCREEN_WIDTH/2.f,y-SCREEN_HEIGHT/2.f };
					}
					x += BLOCK_SIZE;
				}
			}
			y += BLOCK_SIZE;
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