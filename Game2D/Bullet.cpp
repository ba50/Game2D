#include "Bullet.h"
#include "Define.h"
#include "Texture.h"

Bullet::Bullet(float angle, const Vecf2 start_velocit, const Vecf2 position, const std::string &file, std::shared_ptr<Renderer> & ren) :
	Object(0, BLOCK_SIZE, BLOCK_SIZE, width, 0, ren, file, position, Vecf2{ sinf(PI*angle / 180.f)*600.f + start_velocit.x, -cosf(PI*angle / 180.f)*600.f + start_velocit.y }),
	life(true),
	time_to_die(false),
	timer(100),
	death_delay(3),
	death_timer(3)
{
	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });
	clips.push_back(SDL_Rect{ 32,0,static_cast<int>(width), static_cast<int>(height) });
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
