#pragma once

#include <list>
#include <map>

#include "Object.h"

class Bullet;
class Audio;
class Static;

class Character :
	public Object
{
public:
	bool life;

	float delta_angle;
	float drawing_angle;
	float delta_velocity; 
	float max_velocity;
	float health;

	unsigned bullet_trigger, bullet_trigger_base;

	enum class Input { Shot, Jumpe, Left, Right, Down, Up };

	std::map<Input, bool> currentInput;

	std::unique_ptr<Static> engine;

public:
	Character(const Vecf2 position, const std::string &file, std::shared_ptr<Renderer> & ren);

	void Update(const float deltaTime,
		std::vector<std::shared_ptr<Bullet>> &bullet_vector,
		std::shared_ptr<Audio> audio = nullptr);

	void Draw(bool mirror = true) override;

	void Inputs();
	void Collison(std::shared_ptr<Object> obj);
};