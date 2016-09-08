#pragma once

#include "Vec2.h"
#include "Object.h"

class Character;

class Camera
{
public:
	Vecf2 position;
	Vecf2 toCenter;
	Vecf2 velocity;

public:
	Camera(Vecf2 position, float width, float height);
	~Camera();
	Camera(const Camera &cam);

	void MoveTo(std::shared_ptr<Character> cha, float deltaTime);
};
