#pragma once

#include "Object.h"

class Bullet :
	public Object
{
public:
	unsigned int timer, death_timer, death_delay;
	bool time_to_die, life;
public:
	Bullet(const Vecf2 position, float angle, const Vecf2 start_velocity, const std::string &file, std::shared_ptr<Renderer> ren);
	~Bullet();

	void Update(const float deltaTime);
	void Draw() override;

};

