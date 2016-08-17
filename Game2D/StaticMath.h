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

class StaticMath
{
public:

	/*
	* Log an SDL error with some error message to the output stream of our choice
	* @param os The output stream to write the message too
	* @param msg The error message to write, format will be msg error: SDL_GetError()
	*/
	static void logSDLError(std::ostream &os, const std::string &msg);

	/*
	* Loads an image into a texture on the rendering device
	* @param file The image file to load
	* @param ren The renderer to load the texture onto
	* @return the loaded texture, or nullptr if something went wrong.
	*/
	static SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

	/*
	* Draw an SDL_Texture to an SDL_Renderer at some destination rect
	* taking a clip of the texture if desired
	* @param tex The source texture we want to draw
	* @param rend The renderer we want to draw too
	* @param dst The destination rectangle to render the texture too
	* @param clip The sub-section of the texture to draw (clipping rect)
	*		default of nullptr draws the entire texture
	*/
	static void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr);

	/*
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
	static void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr);
};

