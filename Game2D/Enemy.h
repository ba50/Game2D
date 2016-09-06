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
	unsigned int counter;
	bool life;

public:
	Enemy(const float x, const float y, const std::string & file, std::shared_ptr<Renderer> ren);
	~Enemy();

	void Update(const float deltaTime) override;
	void Detect(std::shared_ptr<Character> cha);

	void Enemy::Collision(std::shared_ptr<Static> stat);
	void Enemy::Collision(std::shared_ptr<Bullet> bull);

};

