#pragma once
#include "Moving.h" 

class Character;
class Bullet;
class Static;

class Enemy :
	public Moving
{
public:
	bool max_size;

	Vecf2 scaleMax;

public:
	Enemy(	
	const Vecf2 position,
	const std::string & file,
	const std::vector<SDL_Rect> clips,
	Renderer &ren);

	void Update(const float deltaTimen);

	void Detect(Character &cha);
	void Collision(std::shared_ptr<Bullet> &bull);
	void Collision(Enemy &enemy);
};

