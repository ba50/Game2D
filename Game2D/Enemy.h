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
	unsigned pain;
	bool life;
	Vecf2 scale, scaleMax;
	bool max_size;

public:
	Enemy(const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren);
	~Enemy();

	void Update(const float deltaTime);
	void Draw() override;

	void Detect(std::shared_ptr<Character> cha);

	void Enemy::Collision(std::shared_ptr<Static> stat);
	void Enemy::Collision(std::shared_ptr<Bullet> &bull);

};

