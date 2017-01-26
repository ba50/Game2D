#pragma once

#include <memory>

#include "SDL.h"
#include "Vec2.h"

//Screen attributes
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define BASE_WITH 640
#define BASE_HEIGHT 480

#define BLOCK_SIZE 32

class Object;
class Camera;

class Renderer
{
public:
	SDL_Window *win;
	SDL_Renderer *ren;

	static Vecf2 scale;

	std::shared_ptr<Camera> camera;

public:
	Renderer();
	~Renderer();

	void Clear();
	void RenderPresent();

	void Render(Object &obj, float angle = 0, bool reflection = true, Vecf2 scale = Vecf2{ 1.f,1.f });
};
