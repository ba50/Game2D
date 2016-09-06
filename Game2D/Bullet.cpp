#include "Bullet.h"
#include "Define.h"
#include "Texture.h"

Bullet::Bullet(const Vecf2 position, bool Right, const std::string &file, std::shared_ptr<Renderer> ren):
	life(true)
{
	width = BLOCK_SIZE;
	height = BLOCK_SIZE;
	Object::position = position;
	sprite = std::make_shared<Texture>(file, ren);

	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });

	collisionBox.x = width / 2;
	collisionBox.y = height / 2;

	timer = 75;
	if (Right) {
		velocity = Vecf2{ 600.f,0.f };
	}
	else
	{
		velocity = Vecf2{ -600.f,0.f };
	}
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
