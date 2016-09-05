#pragma once

#include "Vec2.h"
#include "Object.h"

class Camera
{
public:
	Vecf2 position;
	Vecf2 toCenter;

public:
	Camera(Vecf2 position, float width, float height);
	~Camera();
	Camera(const Camera &cam);

	void MoveTo(Vecf2 newPosition);
};
