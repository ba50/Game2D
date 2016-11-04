#pragma once

#include <list>
#include <map>

#include "Object.h"

class Bullet;

class Character :
	public Object
{
public:
	Vecf2 newPosition;
	float delta_angle;

	enum class Input { Shot, Jumpe, Left, Right, Down, Up };

	std::map<Input, bool> currentInput;

	bool life;

public:
	Character(const float x, const float y, const std::string &file, std::shared_ptr<Renderer> & ren);
	~Character();

	void Update(const float deltaTime) override;
	void Draw() override;
	void Inputs();
	void Collison();
};