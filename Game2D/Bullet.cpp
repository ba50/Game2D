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

	velocity.x = sinf(PI*angle / 180.f);
	velocity.y = -cosf(PI*angle/180.f);

	velocity.x = velocity.x*600.f + start_velocity.x;
	velocity.y = velocity.y*600.f + start_velocity.y;

	timer = 50;
}

Bullet::~Bullet()
{
}

void Bullet::Update(const float deltaTime) {
	timer--;

	if (timer <= 0) {
		life = false;
	}

	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;
}

void Bullet::Draw()
{
	ren->render(this);
}
