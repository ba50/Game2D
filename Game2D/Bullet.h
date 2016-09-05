#pragma once
#include "Object.h"
class Bullet :
	public Object
{
public:
	Bullet(const float x, const float y, const std::string &file, SDL_Renderer *ren);
	~Bullet();
};

