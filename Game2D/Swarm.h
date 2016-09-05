#pragma once

#include "Object.h"

#include <list>

#include "Enemy.h"

class Character;

class Swarm :
	public Object
{
public:
	std::list<std::shared_ptr<Enemy>> swarm;

public:
	Swarm(const float x, const float y, const std::string & file, std::shared_ptr<Renderer> ren);
	~Swarm();

	void Update(const float deltaTime) override;
};

