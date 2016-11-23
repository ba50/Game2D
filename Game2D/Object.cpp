#include "Object.h"

#include "Inputs.h"
#include "Character.h"
#include "Texture.h"
#include "Define.h"

std::map<Key, Action> Inputs::key;

Object::Object(

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
	useClip(useClip),
	height(height),
	width(width),
	collision_r(collision_r),
	angle(angle),
	ren(ren),
	sprite{std::make_shared<Texture>(file, ren)},
	position(position),
	velocity(velocity),
	scale(scale)
{}