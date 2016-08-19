#pragma once
#include <memory>

#include "Inputs.h"
#include "cleanup.h"

#include "Vec2.h"

class Object
{
public:

	int useClip;
	float height;
	float width;

	Vecf2 position;
	SDL_Texture *sprite;
	std::vector<SDL_Rect> clips;

	Vecf2 velocity;

public:
	Object();
	virtual ~Object();
	Object(const Object &obj);

	virtual void Update(const float DeltaTime) = 0;
	virtual void Print();

	static bool Collison(std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2);
};

