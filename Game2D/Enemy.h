#pragma once
#include "Object.h" 

#include <map>

class Character;
class Bullet;
class Static;

class Enemy :
	public Object
{
public:
	bool life, time_to_die;
	bool max_size;

	unsigned bullet_trigger, bullet_trigger_base;
	unsigned pain, death_timer, death_delay;

	float health;

	Vecf2 scaleMax;

public:
	Enemy(const Vecf2 position, const std::string &file, std::shared_ptr<Renderer> & ren);

	void Update(const float deltaTime);

	void Detect(std::shared_ptr<Character> cha, std::vector<std::shared_ptr<Bullet>> &bullet_vector);
	void Enemy::Collision(std::shared_ptr<Bullet> &bull);

	void Draw(bool mirror = true) override;
};

