#pragma once

#include <map>

#include "Moving.h"
#include "Engine.h"

#define MAX_HEALTH 255

class Bullet;
class Audio;

class Character :
	public Moving
{
public:

	float delta_angle;
	float drawing_angle;
	float delta_velocity; 
	float max_velocity;
	float recoil;

	enum class Input { Shot, Left, Right, Boost };

	std::map<Input, bool> currentInput;

	std::unique_ptr<Engine> engine;

public:
	Character(	

	const Vecf2 position,
	const std::string & file,
	const std::vector<SDL_Rect> clips,
	Renderer &ren);

	void Update(const float deltaTime);

	void Inputs();
	void Collison(Object &obj);
};