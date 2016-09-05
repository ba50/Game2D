#pragma once
#include <string>
#include <memory>

#include "SDL.h"

class Renderer;

class Texture
{
public:
	SDL_Texture *texture;

public:
	Texture(const std::string &file, std::shared_ptr<Renderer> ren);
	~Texture();
};

