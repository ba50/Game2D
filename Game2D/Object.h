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
	const unsigned animation_delay;
	unsigned current_animation_delay;

	int useClip;
	const int height;
	const int width;

	float angle;

	const std::vector<SDL_Rect> clips;
	const std::shared_ptr<Texture> sprite;

	Vecf2 position;
	Vecf2 velocity;
	Vecf2 scale;
	
public:
	Object(
		unsigned animation_delay,

		int useClip,
		int width,
		int height,

		float angle,

		std::string file,
		std::vector<SDL_Rect> clips,
		Renderer &ren,

		Vecf2 position = Vecf2{ 0.f,0.f },
		Vecf2 velocity = Vecf2{ 0.f, 0.f },
		Vecf2 scale = Vecf2{1.f,1.f}
	);

	void Animation(unsigned start_clip, unsigned end_clip);
	virtual void Draw(Renderer &ren, bool reflection) = 0;
};