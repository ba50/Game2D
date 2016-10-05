#pragma once

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
	Vecf2 collisionBoxX, collisionBoxY, collisionBox;
	
	bool collidable;

public:
	Object(const std::shared_ptr<Renderer> &ren);
	virtual ~Object();
	Object(const Object &obj);

	virtual void Update(const float deltaTime, std::vector<std::shared_ptr<Object>> objectToCollied ) = 0;
	virtual void Draw() = 0;
	virtual void Print();
};