#pragma once

#include <list>
#include <map>

#include "Object.h"

class Bullet;

class Character :
	public Object
{
public:
	Vecf2 newPosition, delta_velocity;
	float delta_angle;
	unsigned bullet_trigger, bullet_trigger_base;

	enum class Input { Shot, Jumpe, Left, Right, Down, Up };

	std::map<Input, bool> currentInput;

	bool life;

public:
	Character(const float x, const float y, const std::string &file, std::shared_ptr<Renderer> & ren);
	~Character();

	void Update(const float deltaTime, std::vector<std::shared_ptr<Bullet>> &bullet_vector);
	void Draw() override;
	void Inputs();
	void Collison();
};