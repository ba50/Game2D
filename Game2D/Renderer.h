#pragma once

#include <memory>

#include "SDL.h"

class Object;
class Camera;

class Renderer
{
public:
	SDL_Window *win;
	SDL_Renderer *ren;

public:
	Renderer();
	~Renderer();

	void Clear();
	void RenderPresent();

	void render(std::shared_ptr<Object> obj, std::shared_ptr<Camera> cam);

};
