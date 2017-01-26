#include "Object.h"

#include "Inputs.h"
#include "Character.h"
#include "Texture.h"
#include "Define.h"

std::map<Key, Action> Inputs::key;

Object::Object(
	unsigned animation_delay,

	int useClip,
	int width,
	int height,

	float angle,
	float collision_r,

	std::string file,
	std::vector<SDL_Rect> clips,
	Renderer &ren,

	Vecf2 position,
	Vecf2 velocity,
	Vecf2 scale
) :
	animation_delay(animation_delay),
	useClip(useClip),
	width(width),
	height(height),
	angle(angle),
	collision_r(collision_r*Renderer::scale.x),
	sprite{ std::make_shared<Texture>(file, ren) },
	clips{ clips },
	position(position),
	velocity(velocity),
	scale(scale)
{
	current_animation_delay = animation_delay;
}

void Object::Animation(unsigned start_clip, unsigned end_clip)
{
	current_animation_delay--;
	if (current_animation_delay == 0) {
		current_animation_delay = animation_delay;

		useClip++;
		if (useClip == end_clip) {
			useClip = start_clip;
		}

	}
}