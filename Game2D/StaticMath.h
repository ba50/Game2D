#pragma once

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "cleanup.h"

#define PI 3.1416

//Screen attributes
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Object;

class StaticMath
{
public:

	/*
	* Log an SDL error with some error message to the output stream of our choice
	* @param os The output stream to write the message too
	* @param msg The error message to write, format will be msg error: SDL_GetError()
	*/
	static void logSDLError(std::ostream &os, const std::string &msg);

	static bool collison(const Object *obj1,const Object *obj2);
};

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
			StaticMath::logSDLError(std::cout, "LoadTexture");
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
	static void render(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr)
	{
		SDL_Rect dst;
		dst.x = x;
		dst.y = y;
		if (clip != nullptr) {
			dst.w = clip->w;
			dst.h = clip->h;
		}
		else {
			SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
		}
		render(tex, ren, dst, clip);
	}
};