#pragma once

#include "Object.h"

class Bullet :
	public Object
{
public:
	unsigned int timer;
public:
	Bullet(const float x, const float y, const std::string &file, std::shared_ptr<Renderer> ren);
	~Bullet();

	void Update(const float deltaTime) override;
};

