#include "Renderer.h"

#include "Define.h"
#include "Object.h"
#include "Texture.h"

#include "cleanup.h"

Vecf2 Renderer::scale;

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

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		Error::LogSDL(std::cout, "CreateRenderer");
	}

	scale.x = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(BASE_WITH);
	scale.y = static_cast<float>(SCREEN_HEIGHT) / static_cast<float>(BASE_HEIGHT);

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
 void Renderer::Render(Object &obj, float angle, bool mirror, Vecf2 scaler)
{
	 SDL_Rect dst, test;
	 dst.x = static_cast<int>(((obj.position.x - (obj.width * Renderer::scale.x) / 2.f) - camera->position.x) / obj.scale.x);
	 dst.y = static_cast<int>(((obj.position.y - (obj.height * Renderer::scale.y) / 2.f) - camera->position.y) / obj.scale.y);

	 if (&obj.clips[obj.useClip] != nullptr) {
		 dst.w = static_cast<int>(obj.width*Renderer::scale.x);
		 dst.h = static_cast<int>(obj.height*Renderer::scale.y);
	 }
	 else {
		 SDL_QueryTexture(obj.sprite->texture, NULL, NULL, &dst.w, &dst.h);
	 }

	 SDL_RenderSetScale(ren, obj.scale.x, obj.scale.y);
	 SDL_SetTextureBlendMode(obj.sprite->texture, SDL_BLENDMODE_BLEND);

	 if ((obj.position.y < Gameplay::water_level && obj.position.y > Gameplay::sky_level) || !mirror) {

		 SDL_RenderCopyEx(ren, obj.sprite->texture, &obj.clips[obj.useClip], &dst, angle, NULL, SDL_FLIP_NONE);
		 SDL_RenderFillRect(ren, &test);
	 }

	 if (obj.position.y < Gameplay::water_level) {
		 dst.y = -static_cast<int>(((obj.position.y + (obj.height * Renderer::scale.y) / 2.f) + camera->position.y) / obj.scale.y);
		 SDL_RenderCopyEx(ren, obj.sprite->texture, &obj.clips[obj.useClip], &dst, -angle, NULL, SDL_FLIP_VERTICAL);
	 }
 }