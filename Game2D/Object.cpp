#include "Object.h"

#include "Inputs.h"
#include "Character.h"
#include "Texture.h"

std::map<Key, Action> Inputs::key;

Object::Object(const std::shared_ptr<Renderer> &ren) :
	useClip(0),
	velocity({0.f,0.f}),
	momentum({0.f,0.f}),
	scale({1.f,1.f}),
	angle(0.f),
	collision_r(1.f),
	health(1.f),
	ren(ren)
{}

Object::~Object()
{}

Object::Object(const Object & obj) :
	useClip(obj.useClip),
	height(obj.height),
	width(obj.width)
{
	position = obj.position;
	sprite = obj.sprite;

	clips = obj.clips;
}