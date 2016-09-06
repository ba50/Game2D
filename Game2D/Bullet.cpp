#include "Bullet.h"
#include "Define.h"
#include "Texture.h"

Bullet::Bullet(const float x, const float y, const std::string &file, std::shared_ptr<Renderer> ren)
{
	width = BLOCK_SIZE;
	height = BLOCK_SIZE;
	position.x = x;
	position.y = y;
	sprite = std::make_shared<Texture>(file, ren);

	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });

	collisionBox.x = width / 2;
	collisionBox.y = height / 2;

	timer = 10;
}

Bullet::~Bullet()
{

}

void Bullet::Update(const float deltaTime) {
	timer--;
	if (timer <= 0) {
		delete this;
	}
}
