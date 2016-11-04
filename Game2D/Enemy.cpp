#include "Enemy.h"

#include "Character.h"

#include "Define.h"
#include "Texture.h"
#include "Bullet.h"
#include "Static.h"

Enemy::Enemy(const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren) :
	Object(ren),
	life(true),
	scale(Vecf2{ 1.f,1.f }),
	max(false)
{
	width = 1;
	height = 1;
	Object::position = position;
	sprite = std::make_shared<Texture>(file, ren);

	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });

	velocity = Vecf2{ 0.f, 0.f };
	scaleMax = Vecf2{ Math::Rand(1.f,7.f), Math::Rand(1.f,7.f) };
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;
	if (scale.x < scaleMax.x && !max)
	{
		scale.x += 0.05f;
		scale.y += 0.05f;
	}
	else {
		max = true;
	}

	if (scale.x >= 1.f && max)
	{
		scale.x -= 0.05f;
		scale.y -= 0.05f;
	}
	else {
		max = false;
	}
}

void Enemy::Draw()
{
	ren->render(this, scale);
}

void Enemy::Detect(std::shared_ptr<Character> cha)
{
	Vecf2 r{ cha->position - position };
	if (sqrt(r.x*r.x + r.y*r.y) < 250.f) {
		velocity.x = (cha->position.x - position.x)*1.2f;
		velocity.y = (cha->position.y - position.y)*1.2f;

		if (sqrt(r.x*r.x + r.y*r.y) < 4.f) {
			cha->life = false;
		}

	}
	else
	{
		if (((float)rand() / RAND_MAX) <= 0.5f) {
			velocity.x += ((float)rand() / RAND_MAX)*5.f;
		}
		else {
			velocity.x -= ((float)rand() / RAND_MAX)*5.f;
		}

		if (((float)rand() / RAND_MAX) <= 0.5f) {
			velocity.y += ((float)rand() / RAND_MAX)*5.f;
		}
		else {
			velocity.y -= ((float)rand() / RAND_MAX)*5.f;
		}

	}
}

void Enemy::Collision(std::shared_ptr<Static> stat)
{
	
}

void Enemy::Collision(std::shared_ptr<Bullet> bull)
{
}

