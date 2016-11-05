#include "Bullet.h"
#include "Define.h"
#include "Texture.h"

Bullet::Bullet(const Vecf2 position, float angle, const Vecf2 start_velocity, const std::string &file, std::shared_ptr<Renderer> ren):
	Object(ren),
	life(true)
{
	width = 32;
	height = 32;
	Object::position = position;
	sprite = std::make_shared<Texture>(file, ren);

	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });
	clips.push_back(SDL_Rect{ 32,0,static_cast<int>(width), static_cast<int>(height) });

	velocity.x = sinf(PI*angle / 180.f);
	velocity.y = -cosf(PI*angle/180.f);

	velocity.x = velocity.x*600.f + start_velocity.x;
	velocity.y = velocity.y*600.f + start_velocity.y;

	timer = 100;
	death_delay = 3;
	death_timer = death_delay;
	collision_r = width;
	time_to_die = false;
}

Bullet::~Bullet()
{
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
