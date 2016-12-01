#pragma once

#include "Object.h"

class Moving :
	public Object
{
public:
	bool life, time_to_die;

	unsigned bullet_trigger, bullet_trigger_base;
	unsigned pain, death_timer, death_delay;

	float health;
	float collision_r;

public:
	Moving(

		const unsigned bullet_trigger_base,
		const unsigned pain,
		const unsigned death_delay,
		const float health,

		const unsigned animation_delay,
		const Vecf2 position,
		const std::string & file,
		const std::vector<SDL_Rect> clips,
		Renderer &ren);

};