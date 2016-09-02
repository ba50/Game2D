#pragma once

#include "Object.h"

class Static :
	public Object
{
public:
public:
	Static(const float x, const float y, const std::string &file, SDL_Renderer *ren);
	virtual ~Static();

	virtual void Update(const float DeltaTime) override;
};

