#pragma once

#include "Object.h"

class Static :
	public Object
{
public:
	Vecf2 root_position;

public:
	Static(SDL_Rect rect, const std::string &file, std::shared_ptr<Renderer> ren);
	Static(const unsigned animation_delay, const std::vector<SDL_Rect> clips_, const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren);

	void Draw(bool mirror = true) override;

	void Update(const float deltaTime);
};

