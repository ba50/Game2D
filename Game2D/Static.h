#pragma once

#include "Object.h"

class Static :
	public Object
{
public:
	Vecf2 root_position;

public:
	Static(const unsigned animation_delay, const std::vector<SDL_Rect> clips_, const Vecf2 position, const std::string & file, Renderer &ren);

	void Draw(Renderer &ren, bool reflection) override;
};