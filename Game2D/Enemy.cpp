#include "Enemy.h"

#include "Character.h"

#include "Define.h"
#include "Texture.h"

unsigned int Enemy::counter = 0;

Enemy::Enemy(const float x, const float y, const std::string & file, std::shared_ptr<Renderer> ren)
{
	width = 16;
	height = 16;
	position.x = x;
	position.y = y;
	sprite = std::make_shared<Texture>(file, ren);

	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });

	collisionBox.x = width / 2;
	collisionBox.y = height / 2;

	velocity = Vecf2{ 0.f, 0.f };

	counter++;
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

		velocity.x = (cha->position.x - position.x)*5.f;
		velocity.y = (cha->position.y - position.y)*5.f;
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
	if ((position.x - collisionBox.x) < (obj->position.x + obj->collisionBox.x) &&
		(position.x + collisionBox.x) > (obj->position.x - obj->collisionBox.x) &&
		((position.y - collisionBox.y)  ) < ((obj->position.y + obj->collisionBox.y)) &&
		((position.y - collisionBox.y) ) > ((obj->position.y + obj->collisionBox.y) )) {
//		currentStates[States::CanJumpe] = false;
		velocity.y *= -1;
	}

	if ((position.x - collisionBox.x) < (obj->position.x + obj->collisionBox.x) &&
		(position.x + collisionBox.x) > (obj->position.x - obj->collisionBox.x) &&
		((position.y + collisionBox.y) ) < ((obj->position.y - obj->collisionBox.y) ) &&
		((position.y + collisionBox.y) ) > ((obj->position.y - obj->collisionBox.y) )) {
//		currentStates[States::CanFall] = false;
//		currentStates[States::OnFloor] = true;
		velocity.y *= 1;
	}

	if (((position.x - collisionBox.x)) < ((obj->position.x + obj->collisionBox.x)) &&
		((position.x - collisionBox.x) ) > ((obj->position.x + obj->collisionBox.x)) &&
		(position.y - collisionBox.y) < (obj->position.y + obj->collisionBox.y) &&
		(position.y + collisionBox.y) > (obj->position.y - obj->collisionBox.y)) {
//		currentStates[States::CanLeft] = false;
		velocity.x *= -1;
	}

	if (((position.x + collisionBox.x)) < ((obj->position.x - obj->collisionBox.x) ) &&
		((position.x + collisionBox.x)) > ((obj->position.x - obj->collisionBox.x) ) &&
		(position.y - collisionBox.y) < (obj->position.y + obj->collisionBox.y) &&
		(position.y + collisionBox.y) > (obj->position.y - obj->collisionBox.y)) {
//		currentStates[States::CanRight] = false;
		velocity.x *= -1;
	}

}
