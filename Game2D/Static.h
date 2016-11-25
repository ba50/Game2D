#pragma once

#include "Object.h"

class Static :
	public Object
{
public:
	unsigned animation_delay, current_animation_delay;

public:
	Static(const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren);
	Static(SDL_Rect rect, const std::string &file, std::shared_ptr<Renderer> ren);
	Static(const std::vector<SDL_Rect> clips_, const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren);

	void Animation(unsigned start, unsigned end);
	void Draw() override;
};

