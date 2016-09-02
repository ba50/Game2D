#include "Bullet.h"
#include "Define.h"

Bullet::Bullet(const float x, const float y, const std::string &file, SDL_Renderer *ren)
{
	width = 32;
	height = 32;
	position.x = x;
	position.y = y;
	sprite = Texture::load(file, ren);

	if (sprite == nullptr)
		throw std::exception("shit!");

	SDL_Rect clipTemp;
	for (int i = 0; i < 4; ++i) {
		clipTemp.x = i * static_cast<int>(width);
		clipTemp.y = static_cast<int>(height);
		clipTemp.w = static_cast<int>(width);
		clipTemp.h = static_cast<int>(height);

		clips.push_back(clipTemp);

	}

	Inputs::slope.push_back(false);
	Inputs::slope.push_back(false);

	collisionBox.x = width / 2;
	collisionBox.y = height / 2;
}


Bullet::~Bullet()
{
	cleanup(sprite);
}
