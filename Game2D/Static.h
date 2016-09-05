#pragma once

#include "Object.h"

class Static :
	public Object
{
public:
public:
	Static(const float x, const float y, const std::string &file, std::shared_ptr<Renderer> ren);
	Static(SDL_Rect rect, const std::string &file, std::shared_ptr<Renderer> ren);
	~Static();

	void Update(const float deltaTime) override;
};

