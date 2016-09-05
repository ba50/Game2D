#pragma once

#include <vector>
#include <memory>

#include "SDL.h"

#include "Vec2.h"

class Texture;
class Renderer;

class Object
{
public:

	int useClip;
	float height;
	float width;

	std::shared_ptr<Texture> sprite;
	std::vector<SDL_Rect> clips;

	Vecf2 position;
	Vecf2 velocity;
	Vecf2 collisionBoxX, collisionBoxY, collisionBox;

public:
	Object();
	virtual ~Object();
	Object(const Object &obj);

	virtual void Update(const float deltaTime) = 0;
	virtual void Print();
};

