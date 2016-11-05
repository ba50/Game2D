#pragma once

#include <list>
#include <map>

#include "Object.h"

class Bullet;
class Audio;

class Character :
	public Object
{
public:
	Vecf2 newPosition, delta_force, force, max_momentum;
	float delta_angle;
	unsigned bullet_trigger, bullet_trigger_base;

	enum class Input { Shot, Jumpe, Left, Right, Down, Up };

	std::map<Input, bool> currentInput;

	bool life;

public:
	Character(const float x, const float y, const std::string &file, std::shared_ptr<Renderer> & ren);
	~Character();

	void Update(const float deltaTime,
		std::vector<std::shared_ptr<Bullet>> &bullet_vector,
		std::shared_ptr<Audio> audio = nullptr);
	void Draw() override;
	void Inputs();
	void Collison(std::shared_ptr<Object> obj);
};