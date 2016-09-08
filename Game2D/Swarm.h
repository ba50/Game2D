#pragma once

#include "Object.h"

#include <list>

#include "Enemy.h"

class Character;

class Swarm :
	public Object
{
public:
	std::list<std::shared_ptr<Enemy>> enemyList;
	std::list<std::list<std::shared_ptr<Enemy>>::iterator> toDelete;

public:
	Swarm(Vecf2 position, const std::string & file, const std::shared_ptr<Renderer> ren);
	~Swarm();

	void Update(const float deltaTime) override;
	void Draw() override;

	void Detect(std::shared_ptr<Character> cha);
};

