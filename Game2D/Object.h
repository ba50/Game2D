#pragma once

#include "StaticMath.h"
#include "Vec2.h"

class Object
{
public:

	int useClip;
	int imageH;
	int imageW;
	float radius;

	Vecf2 pos;
	SDL_Texture *sprite;
	std::vector<SDL_Rect> clips;

	float mass;
	Vecf2 momentum; 

public:
	Object(const float x, const float y, const std::string &file, SDL_Renderer *ren);
	virtual ~Object();
	Object(const Object &obj);

	void Update(const float DeltaTime);
	static void Collision(Vecf2 &v1, Vecf2 &v);
	void Print();
};

