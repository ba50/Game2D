#pragma once

#include "Object.h"

class Bullet :
	public Object
{
public:
	bool life, time_to_die;
	unsigned int timer, death_timer, death_delay;

public:
	Bullet(float angle, const Vecf2 start_velocit, const Vecf2 position, const std::string &file, std::shared_ptr<Renderer> & ren);

	void Update(const float deltaTime);

	void Draw(bool mirror = true) override;
};

