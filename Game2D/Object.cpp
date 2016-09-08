#include "Object.h"

#include "Inputs.h"
#include "Character.h"
#include "Texture.h"

std::map<Key, Action> Inputs::key;

Object::Object(const std::shared_ptr<Renderer> &ren) :
	useClip(0),
	velocity({0.f,0.f}),
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

void Object::Print()
{
	printf("%.1f, %.1f\n", position.x, position.y);
}