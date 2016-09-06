#pragma once

#include "Object.h"

class Bullet :
	public Object
{
public:
	unsigned int timer;
	bool life;
public:
	Bullet(const Vecf2 position, bool Right, const std::string &file, std::shared_ptr<Renderer> ren);
	~Bullet();

	void Update(const float deltaTime) override;
};

