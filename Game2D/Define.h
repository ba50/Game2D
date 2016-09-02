#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>

#include "Camera.h"
#include "Character.h"
#include "Static.h"

#define PI 3.1416f
#define g 9.81f 

//Screen attributes
#define SCREEN_WIDTH 1270 
#define SCREEN_HEIGHT 600

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

namespace Texture {
	/*
	* Loads an image into a texture on the rendering device
	* @param file The image file to load
	* @param ren The renderer to load the texture onto
	* @return the loaded texture, or nullptr if something went wrong.
	*/
	static SDL_Texture* load(const std::string &file, SDL_Renderer *ren)
	{
		SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
		if (texture == nullptr) {
			Error::logSDL(std::cout, "LoadTexture");
		}
		return texture;
	}

	/*
	* Draw an SDL_Texture to an SDL_Renderer at some destination rect
	* taking a clip of the texture if desired
	* @param tex The source texture we want to draw
	* @param rend The renderer we want to draw too
	* @param dst The destination rectangle to render the texture too
	* @param clip The sub-section of the texture to draw (clipping rect)
	*		default of nullptr draws the entire texture
	*/
	static void render(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr)
	{
		SDL_RenderCopy(ren, tex, clip, &dst);
	}

	/**
	* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
	* the texture's width and height and taking a clip of the texture if desired
	* If a clip is passed, the clip's width and height will be used instead of the texture's
	* @param tex The source texture we want to draw
	* @param rend The renderer we want to draw too
	* @param x The x coordinate to draw too
	* @param y The y coordinate to draw too
	* @param clip The sub-section of the texture to draw (clipping rect)
	*		default of nullptr draws the entire texture
	*/
	static void render(SDL_Texture *tex, SDL_Renderer *ren, std::shared_ptr<Object> obj, std::shared_ptr<Camera> cam)
	{
		SDL_Rect dst;
		dst.x = static_cast<int>(obj->position.x - cam->position.x);
		dst.y = static_cast<int>(obj->position.y - cam->position.y);

		if (&obj->clips[obj->useClip] != nullptr) {
			dst.w = static_cast<int>(obj->width);
			dst.h = static_cast<int>(obj->height);
		}
		else {
			SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
		}

		render(tex, ren, dst, &obj->clips[obj->useClip]);

		//SDL_SetRenderDrawColor(ren, 255, 0, 0, 5);
		//SDL_Rect test;
		//test.x = dst.x;
		//test.y = dst.y;
		//test.h = obj->collisionBox.y*2;
		//test.w = obj->collisionBox.x*2;
		//SDL_RenderFillRect(ren, &test);
		//SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	}

}

namespace Map {
	static void load(const std::string &file, std::shared_ptr<Character> &player, std::vector<std::shared_ptr<Static>> &floorVect, SDL_Renderer *ren){
		std::ifstream in;
		in.open(file);
		std::string buffer;
		float x=0, y=0;
		while (!in.eof()) {
			in >> buffer;
			for (auto& c : buffer) {
				if (c != ';') {
					if (c == '_' || c=='#') {
						floorVect.push_back(std::make_shared<Static>(x, y, "bkMaze.png", ren));
					}
					if (c == '@') {
						player = std::make_shared<Character>(x, y, "MyChar.png", ren);
					}
					x += 64;
				}
			}
			y += 64;
			x = 0;
		}
	}
}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}