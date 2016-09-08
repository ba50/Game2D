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
	Vecf2 scale;

public:
	Enemy(const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren);
	~Enemy();

	void Update(const float deltaTime) override;
	void Draw() override;

	void Detect(std::shared_ptr<Character> cha);

	void Enemy::Collision(std::shared_ptr<Static> stat);
	void Enemy::Collision(std::shared_ptr<Bullet> bull);

};

