#include "Enemy.h"

#include "Character.h"

#include "Define.h"
#include "Texture.h"
#include "Bullet.h"
#include "Static.h"
#include "Gameplay.h"

Enemy::Enemy(const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> & ren) :
	Object(0, 0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0, ren, file, position, Vecf2{ 0.f, 0.f }),
	life(true),
	time_to_die(false),
	max_size(false),
	bullet_trigger_base(50),
	bullet_trigger(50),
	pain(0),
	death_delay(2),
	death_timer(2),
	health(10.f),
	scaleMax( Vecf2{ Math::Rand(1.f,2.f), Math::Rand(1.f,2.f) })
{
	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });
	clips.push_back(SDL_Rect{ 32,0,static_cast<int>(width), static_cast<int>(height) });
	clips.push_back(SDL_Rect{ 0,32,static_cast<int>(width), static_cast<int>(height) });
	clips.push_back(SDL_Rect{ 32,32,static_cast<int>(width), static_cast<int>(height) });
}

void Enemy::Update(const float deltaTime)
{
	
	if (scale.x < scaleMax.x && !max_size){
		scale.x += 0.05f;
		scale.y += 0.05f;
	}
	else {
		max_size = true;
	}

	if (scale.x >= 1.f && max_size){
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

	if (time_to_die) {
		death_timer--;
		useClip = 3;
		if (death_timer == 0) life = false;
	}

	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;
}

void Enemy::Draw(bool mirror)
{
	ren->Render(this, 0.f, true, scale);
}

void Enemy::Detect(std::shared_ptr<Character> cha, std::vector<std::shared_ptr<Bullet>> &bullet_vector)
{
	Vecf2 r{ cha->position - position };
	if (sqrt(r.x*r.x + r.y*r.y) < SCREEN_WIDTH/4.f) {
		velocity.x = (cha->position.x - position.x)*1.2f;
		velocity.y = (cha->position.y - position.y)*1.2f;

		if (bullet_trigger == 0) {
			if (velocity.y < 0) {
				angle = 180.f*atan(velocity.x / abs(velocity.y)) / PI;
			}
			else {
				angle = 180.f-180.f*atan(velocity.x / abs(velocity.y)) / PI;
			}


			bullet_vector.push_back(std::make_shared<Bullet>(angle, velocity, position, "Source/Bullet.png", ren));
			bullet_trigger = bullet_trigger_base;
		}
		bullet_trigger--;

	}
	else{
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

void Enemy::Collision(std::shared_ptr<Bullet> &bull)
{
	if (sqrtf(
		(bull->position.x - position.x)*(bull->position.x - position.x) +
		(bull->position.y - position.y)*(bull->position.y - position.y)) <
		(bull->collision_r/2.f + collision_r/2.f)) {
		health -= 1.5;
		if (health <= 0.f) {
			time_to_die = true;
		}
		bull->time_to_die = true;
		Gameplay::score = true;
		pain = 3;
	}
}

