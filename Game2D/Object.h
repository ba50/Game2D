#pragma once

#include <forward_list>
#include <vector>
#include <memory>

#include "SDL.h"

#include "Vec2.h"

class Texture;
class Renderer;
class Camera;

class Object
{
public:

	int useClip;
	float height;
	float width;

	std::shared_ptr<Renderer> ren;
	std::shared_ptr<Texture> sprite;
	std::vector<SDL_Rect> clips;

	Vecf2 position;
	Vecf2 velocity;
	Vecf2 momentum;
	float mass;
	Vecf2 scale;
	float angle;
	
	bool collidable;

public:
	Object(const std::shared_ptr<Renderer> &ren);
	virtual ~Object();
	Object(const Object &obj);

	virtual void Draw() = 0;
};