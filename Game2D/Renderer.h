#pragma once

#include <memory>

#include "SDL.h"
#include "Vec2.h"

class Object;
class Camera;

class Renderer
{
public:
	SDL_Window *win;
	SDL_Renderer *ren;

	std::shared_ptr<Camera> camera;

public:
	Renderer();
	~Renderer();

	void Clear();
	void RenderPresent();

	void Render(Object * obj, float angle = 0, bool mirror = true, Vecf2 scale = Vecf2{ 1.f,1.f }, SDL_Point *center = NULL);
};
