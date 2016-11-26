#include "Renderer.h"

#include "Define.h"
#include "Object.h"
#include "Texture.h"

#include "cleanup.h"

Renderer::Renderer()
{
//	Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		Error::LogSDL(std::cout, "SDL_Init_Video");
	}

//	Setup our window and renderer
	win = SDL_CreateWindow("Game 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		Error::LogSDL(std::cout, "CreateWindow");
	}

	ren= SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		Error::LogSDL(std::cout, "CreateRenderer");
	}

	camera = std::make_shared<Camera>(Vecf2{ 0.f,0.f }, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT));
}

Renderer::~Renderer()
{
	cleanup(win, ren);
}


void Renderer::Clear()
{
	SDL_RenderClear(ren);
}

void Renderer::RenderPresent()
{
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderPresent(ren);
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

void Renderer::render(Object * obj, Vecf2 scale, float angle, SDL_Point *center)
{
	if (obj != nullptr) {
		SDL_Rect dst;
		dst.x = static_cast<int>(((obj->position.x - obj->width / 2.f) - camera->position.x)/scale.x);
		dst.y = static_cast<int>(((obj->position.y - obj->height / 2.f) - camera->position.y)/scale.y);

		if (&obj->clips[obj->useClip] != nullptr) {
			dst.w = static_cast<int>(obj->width);
			dst.h = static_cast<int>(obj->height);
		}
		else {
			SDL_QueryTexture(obj->sprite->texture, NULL, NULL, &dst.w, &dst.h);
		}

		SDL_RenderSetScale(ren, scale.x, scale.y);
		SDL_SetTextureBlendMode(obj->sprite->texture, SDL_BLENDMODE_BLEND);

		//Normal
		SDL_RenderCopyEx(ren, obj->sprite->texture, &obj->clips[obj->useClip], &dst, angle, NULL, SDL_FLIP_NONE);
		SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
		SDL_RenderDrawPoint(ren, (int)dst.x+BLOCK_SIZE, (int)dst.y+BLOCK_SIZE);

		//Mirror
	//	dst.y = -static_cast<int>(((obj->position.y - obj->height / 2.f) + camera->position.y)/scale.y);
	////	if (dst.y > WATER_LEVEL - 300)
	//		SDL_RenderCopyEx(ren, obj->sprite->texture, &obj->clips[obj->useClip], &dst, -angle, center, SDL_FLIP_VERTICAL);

	//		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	//		if(center!=NULL)
	//			SDL_RenderDrawPoint(ren, (int)dst.x, (int)dst.y);
	}
}
