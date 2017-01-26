#pragma once

#include "Object.h"

class Engine :
	public Object
{
public:
	Engine(
		const unsigned animation_delay,
		const float angle,
		const Vecf2 position,
		const std::string & file,
		const std::vector<SDL_Rect> clips,
		Renderer &ren);

};

