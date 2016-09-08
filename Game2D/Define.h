#pragma once

#include <iostream>
#include <string>
#include <fstream>

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
#define SCREEN_WIDTH 1068
#define SCREEN_HEIGHT 600
#define BLOCK_SIZE 64;

namespace Error
{
	/*
	* Log an SDL error with some error message to the output stream of our choice
	* @param os The output stream to write the message too
	* @param msg The error message to write, format will be msg error: SDL_GetError()
	*/
	static void logSDL(std::ostream &os, const std::string &msg)
	{
		os << msg << " error: " << SDL_GetError() << std::endl;
		throw std::exception("shit!");
	}
}

namespace Map {
	static void load(const std::string &file, std::shared_ptr<Character> &player, std::vector<std::shared_ptr<Swarm>> &swarmVect, std::vector<std::shared_ptr<Static>> &floorVect,
					std::shared_ptr<Static> &backgroung, std::shared_ptr<Renderer> ren) {
		
		std::ifstream in;
		in.open(file);
		std::string buffer;
		float x=0, y=0;
		while (!in.eof()) {
			in >> buffer;
			for (auto& c : buffer) {
				if (c != ';') {
					if (c == '_' || c=='|') {
						floorVect.push_back(std::make_shared<Static>(Vecf2{ x,y }, "bkBlue.png", ren, true));
					}
					if (c=='#') {
						floorVect.push_back(std::make_shared<Static>(Vecf2{ x,y }, "bkBlue.png", ren));
					}
					if (c == 'W') {
						floorVect.push_back(std::make_shared<Static>(Vecf2{ x,y }, "bkWater.png", ren));
					}
					if (c == '@') {
						player = std::make_shared<Character>(x, y, "MyChar.png", ren);
						backgroung = std::make_shared<Static>(SDL_Rect{ (int)x, (int)y, 7680, 640 }, "BG.png", ren);
						ren->camera->position = Vecf2{ x,y };
					}
					if (c == '!') {
						swarmVect.push_back(std::make_shared<Swarm>(Vecf2{ x,y }, "bkMaze.png", ren));
					}
					x += BLOCK_SIZE;
				}
			}
			y += BLOCK_SIZE;
			x = 0;
		}
	}

}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}