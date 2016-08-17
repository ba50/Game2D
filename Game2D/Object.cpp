#include "Object.h"

Object::Object(const float x, const float y, const std::string &file, SDL_Renderer *ren) :
	useClip(0),
	imageH(100),
	imageW(100),
	radius(49.f),
	mass(100)
{
	pos.x = x;
	pos.y = y;
	sprite = Texture::load(file, ren);

	if (sprite == nullptr)
		throw std::exception( "shit!" );

	momentum = { 0.f, 0.f };

	SDL_Rect clipTemp;
	for (int i = 0; i < 4; ++i) {

		clipTemp.x = i / 2 * imageW;
		clipTemp.y = i % 2 * imageH;
		clipTemp.w = imageW;
		clipTemp.h = imageH;

		clips.push_back(clipTemp);
	}

}

Object::~Object()
{
	cleanup(sprite);
}

Object::Object(const Object & obj) :
	useClip(obj.useClip),
	imageH(obj.imageH),
	imageW(obj.imageW),
	radius(obj.radius),
	mass(obj.mass)
{
	pos = obj.pos;
	sprite = obj.sprite;

	if (sprite == nullptr)
		throw std::exception("shit!");

	momentum = obj.momentum;
	clips = obj.clips;
}

void Object::Update(const float DeltaTime)
{
	pos.x = pos.x + (momentum.x / mass)*DeltaTime;
	pos.y = pos.y + (momentum.y / mass)*DeltaTime;

	if (pos.x <= 0) {
		momentum.x *= -1;
	}
	if (pos.x >= SCREEN_WIDTH - imageW) {
		momentum.x *= -1;
	}

	if (pos.y <= 0) {
		momentum.y *= -1;
	}
	if (pos.y >= SCREEN_HEIGHT - imageH) {
		momentum.y *= -1;
	}
}

void Object::Collision(Vecf2 &v1, Vecf2 &v2)
{
	Vecf2 temp{ v1 };
	v1 = v2;
	v2 = temp;
}

void Object::Print()
{
	printf("%.1f, %.1f\n", pos.x, pos.y);
}
