#include "Bullet.h"
#include "Define.h"
#include "Texture.h"

#define START_VELOCITY 400.f

Bullet::Bullet(

		Vecf2 start_velocity,
	
		const float angle,
		const Vecf2 position,
		const std::string & file,
		const std::vector<SDL_Rect> clips,
		Renderer &ren,
		const Vecf2 scale

) :
	Object(0, 0, clips[0].w, clips[0].h, angle, clips[0].w/2.f, file, clips, ren, position, Vecf2{ START_VELOCITY*sinf(PI*angle / 180.f)+ start_velocity.x, -START_VELOCITY*cosf(PI*angle / 180.f) + start_velocity.y }, scale),

	life(true),
	time_to_die(false),
	timer(100),
	death_delay(3),
	death_timer(3)
{}

void Bullet::Update(const float deltaTime) {
	timer--;

	if (timer <= 0) time_to_die = true;
	
	if (time_to_die) {
		death_timer--;
		useClip = 1;
		if(death_timer==0) life = false;
	}


	if (death_timer >= death_delay) {
		position.x += velocity.x*deltaTime;
		position.y += velocity.y*deltaTime;
	}
}
