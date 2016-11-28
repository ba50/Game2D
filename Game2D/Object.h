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
	unsigned animation_delay, current_animation_delay;

	int useClip;

	float height;
	float width;
	float collision_r;
	float angle;

	std::shared_ptr<Renderer> ren;
	std::shared_ptr<Texture> sprite;
	std::vector<SDL_Rect> clips;

	Vecf2 position;
	Vecf2 velocity;
	Vecf2 scale;
	
public:
	Object(
		unsigned animation_delay,

		int useClip,
		float height,
		float width,
		float collision_r,
		float angle,

		std::shared_ptr<Renderer> ren,
		std::string file,

		Vecf2 position,
		Vecf2 velocity,
		Vecf2 scale = Vecf2{1.f,1.f}
	);

	void Animation(unsigned start_clip, unsigned end_clip);

	virtual void Draw(bool mirror) = 0;
};