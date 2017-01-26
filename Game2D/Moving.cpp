#include "Moving.h"

Moving::Moving(
		const unsigned bullet_trigger_base,
		const unsigned pain,
		const unsigned death_delay,
		const int health,

		const unsigned animation_delay,
		const float collision_r,
		const Vecf2 position,
		const std::string & file,
		const std::vector<SDL_Rect> clips,
		Renderer &ren
) :
	Object(animation_delay, 0, clips[0].w, clips[0].h, 0, collision_r, file, clips, ren, position),

	life(true),
	time_to_die(false),
	shoot(false),
	bullet_trigger_base(bullet_trigger_base),
	pain(pain),
	death_delay(death_delay),
	health(health)
{
	bullet_trigger = bullet_trigger_base;
	death_timer = death_delay;
}