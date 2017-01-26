#pragma once

#include "Object.h"

class Bullet :
	public Object
{
public:
	bool life, time_to_die;
	unsigned int timer, death_timer, death_delay;

public:
	Bullet(

		Vecf2 start_velocity,
	
		const float angle,
		const Vecf2 position,
		const std::string & file,
		const std::vector<SDL_Rect> clips,
		Renderer &ren,
		const Vecf2 scale = Vecf2{ 1.f, 1.f });

	void Update(const float deltaTime);
};

