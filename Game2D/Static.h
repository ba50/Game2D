#pragma once

#include "Object.h"

class Static :
	public Object
{
public:
public:
	Static(const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren, bool collidable=false);
	Static(SDL_Rect rect, const std::string &file, std::shared_ptr<Renderer> ren);
	~Static();

	void Update(const float deltaTime);
	void Draw() override;
};

