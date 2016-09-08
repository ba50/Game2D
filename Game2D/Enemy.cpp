#include "Enemy.h"

#include "Character.h"

#include "Define.h"
#include "Texture.h"
#include "Bullet.h"
#include "Static.h"

Enemy::Enemy(const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren) :
	Object(ren),
	life(true),
	scale(Vecd2{1.f,1.f})
{
	width = 4;
	height = 4;
	Object::position = position;
	sprite = std::make_shared<Texture>(file, ren);

	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });

	collisionBox.x = width / 2;
	collisionBox.y = height / 2;

	velocity = Vecf2{ 0.f, 0.f };
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;
}

void Enemy::Draw()
{
	ren->render(this);
}

void Enemy::Detect(std::shared_ptr<Character> cha)
{
	Vecf2 r{ cha->position - position };
	if (abs(sqrt(r.x*r.x + r.y*r.y)) < 150.f) {
		velocity.x = (cha->position.x - position.x);
		velocity.y = (cha->position.y - position.y);
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
	if (stat->collidable)
	{
		Vecf2 r{ stat->position.x - position.x, stat->position.y - position.y };
		if (sqrt(r.x*r.x + r.y*r.y) < (stat->collisionBox.x + collisionBox.x)) {
			velocity.x = -r.x;
			velocity.y = -r.y;
		}
	}
}

void Enemy::Collision(std::shared_ptr<Bullet> bull)
{
	Vecf2 r{ bull->position.x - position.x, bull->position.y - position.y };
	if (sqrt(r.x*r.x + r.y*r.y) < (bull->collisionBox.x + collisionBox.x)) {
		life = false;
	}
}

