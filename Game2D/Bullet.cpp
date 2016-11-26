#include "Bullet.h"
#include "Define.h"
#include "Texture.h"

#define START_VELOCITY 400.f

Bullet::Bullet(float angle, const Vecf2 start_velocit, const Vecf2 position, const std::string &file, std::shared_ptr<Renderer> & ren) :
	Object(0, 0, BLOCK_SIZE/2, BLOCK_SIZE/2, width, 0, ren, file, position, Vecf2{ START_VELOCITY*sinf(PI*angle / 180.f)+ start_velocit.x, -START_VELOCITY*cosf(PI*angle / 180.f) + start_velocit.y }),
	life(true),
	time_to_die(false),
	timer(100),
	death_delay(3),
	death_timer(3)
{
	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });
	clips.push_back(SDL_Rect{ BLOCK_SIZE/2,0,static_cast<int>(width), static_cast<int>(height) });
}

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

void Bullet::Draw()
{
	ren->render(this);
}
