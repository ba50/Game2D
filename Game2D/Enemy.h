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

private:
	bool shot;

public:
	Enemy(	

	const unsigned bullet_trigger_base,
	const unsigned pain,
	const unsigned death_delay,
	const float health,

	const unsigned animation_delay, 
	const Vecf2 position,
	const std::string & file,
	const std::vector<SDL_Rect> clips,
	Renderer &ren);

	void Update(const float deltaTime, std::vector<std::shared_ptr<Bullet>> &bullet_vector, Renderer &ren);

	void Detect(Character &cha);
	void Collision(std::shared_ptr<Bullet> &bull);

	void Draw(Renderer &ren, bool reflection = true) override;
};

