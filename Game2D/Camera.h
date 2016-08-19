#pragma once

#include "Vec2.h"
#include "Object.h"

class Camera
{
public:
	Vecf2 position;
	Vecf2 toCenter;

public:
	Camera(float width, float height);
	virtual ~Camera();
	Camera(const Camera &cam);

	void MoveTo(Vecf2 newPosition);
};
