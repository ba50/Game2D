#include "Enemy.h"

#include "Character.h"

#include "Define.h"
#include "Texture.h"
#include "Bullet.h"
#include "Static.h"
#include "Gameplay.h"



Enemy::Enemy(const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren) :
	Object(ren),
	life(true),
	scale(Vecf2{ 1.f,1.f }),
	max_size(false)
{
	width = BLOCK_SIZE;
	height = BLOCK_SIZE;
	Object::position = position;
	sprite = std::make_shared<Texture>(file, ren);

	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });
	clips.push_back(SDL_Rect{ 32,0,static_cast<int>(width), static_cast<int>(height) });
	clips.push_back(SDL_Rect{ 0,32,static_cast<int>(width), static_cast<int>(height) });

	velocity = Vecf2{ 0.f, 0.f };
	scaleMax = Vecf2{ Math::Rand(1.f,7.f), Math::Rand(1.f,7.f) };
	collision_r = width;
	health = 10.f;
	pain = 0;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;
	if (scale.x < scaleMax.x && !max_size)
	{
		scale.x += 0.05f;
		scale.y += 0.05f;
	}
	else {
		max_size = true;
	}

	if (scale.x >= 1.f && max_size)
	{
		scale.x -= 0.05f;
		scale.y -= 0.05f;
	}
	else {
		max_size = false;
	}

	collision_r = scale.x*width;

	if (health > 3.f) {
		useClip = 0;
	}
	else {
		useClip = 1;
	}

	if (pain > 0) {
		useClip = 2;
		pain--;
	}
}

void Enemy::Draw()
{
	ren->render(this, scale);
}

void Enemy::Detect(std::shared_ptr<Character> cha)
{
	Vecf2 r{ cha->position - position };
	if (sqrt(r.x*r.x + r.y*r.y) < SCREEN_WIDTH/4.f) {
		velocity.x = (cha->position.x - position.x)*1.2f;
		velocity.y = (cha->position.y - position.y)*1.2f;

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

void Enemy::Collision(std::shared_ptr<Bullet> &bull)
{
	if (sqrtf(
		(bull->position.x - position.x)*(bull->position.x - position.x) +
		(bull->position.y - position.y)*(bull->position.y - position.y)) <
		(bull->collision_r/2.f + collision_r/2.f)) {
		health -= 1.5;
		if (health <= 0.f) {
			life = false;
		}
		bull->life = false;
		Gameplay::score = true;
		pain = 3;
	}
}

