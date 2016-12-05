#pragma once

#include <map>

#include "Moving.h"

class Bullet;
class Audio;
class Static;

class Character :
	public Moving
{
public:

	float delta_angle;
	float drawing_angle;
	float delta_velocity; 
	float max_velocity;

	enum class Input { Shot, Jumpe, Left, Right, Down, Up };

	std::map<Input, bool> currentInput;

//	std::unique_ptr<Static> engine;

public:
	Character(	

	const unsigned bullet_trigger_base,
	const unsigned pain,
	const unsigned death_delay,
	const float health,

	const unsigned animation_delay, 
	const Vecf2 position,
	const std::string & file,
	const std::vector<SDL_Rect> clips,
	Renderer &ren);

	void Update(const float deltaTime,
		std::vector<std::shared_ptr<Bullet>> &bullet_vector,
		Audio &audio);

	void Draw(Renderer &ren, bool reflection  = true) override;

	void Inputs();
	void Collison(std::shared_ptr<Object> obj);
};