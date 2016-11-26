#include "Object.h"

#include "Inputs.h"
#include "Character.h"
#include "Texture.h"
#include "Define.h"

std::map<Key, Action> Inputs::key;

Object::Object(
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
		Vecf2 scale
	) :
	animation_delay(animation_delay),
	current_animation_delay(1),
	useClip(useClip),
	height(height),
	width(width),
	collision_r(collision_r),
	angle(angle),
	ren(ren),
	sprite{ std::make_shared<Texture>(file, ren) },
	position(position),
	velocity(velocity),
	scale(scale)
{}

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