#include "Enemy.h"

#include "Character.h"

#include "Define.h"
#include "Texture.h"

Enemy::Enemy(const float x, const float y, const std::string & file, std::shared_ptr<Renderer> ren)
{
	width = 4;
	height = 4;
	position.x = x;
	position.y = y;
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
	if (currentStates[States::Detect]) {

	}

	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;
}

void Enemy::Detect(std::shared_ptr<Character> cha)
{
	Vecf2 r{ cha->position - position };
	if (abs(sqrt(r.x*r.x + r.y*r.y)) < 150.f) {
		currentStates[States::Detect] = true;

		velocity.x = (cha->position.x - position.x);
		velocity.y = (cha->position.y - position.y);
	}
	else
	{
		if (((float)rand() / RAND_MAX) <= 0.5f) {
			velocity.x += ((float)rand() / RAND_MAX);
		}
		else {
			velocity.x -= ((float)rand() / RAND_MAX);
		}

		if (((float)rand() / RAND_MAX) <= 0.5f) {
			velocity.y += ((float)rand() / RAND_MAX);
		}
		else {
			velocity.y -= ((float)rand() / RAND_MAX);
		}

	}
}

void Enemy::Collision(std::shared_ptr<Object> obj)
{
	Vecf2 r{ obj->position.x - position.x, obj->position.y - position.y };
	if (sqrt(r.x*r.x + r.y*r.y) < (obj->collisionBox.x + collisionBox.x)) {
		velocity.x = -r.x;
		velocity.y = -r.y;
	}
}
