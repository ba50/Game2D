#pragma once

#include "Object.h"

class Static :
	public Object
{
public:
	Static(
		const Vecf2 position, 
		const std::string & file,
		const std::vector<SDL_Rect> clips,
		Renderer &ren);

	void Update(const float deltaTime) {
		position.x += velocity.x*deltaTime;
	}
};