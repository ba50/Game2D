#include "Object.h"
#include "Character.h"

std::map<Key, Action> Inputs::key;

Object::Object() :
	useClip(0),
	velocity({0.f,0.f})
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

	if (sprite == nullptr)
		throw std::exception("shit!");

	clips = obj.clips;
}
void Object::Print()
{
	printf("%.1f, %.1f\n", position.x, position.y);
}

bool Object::Collison(std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2)
{
	Vecf2 r = { abs(obj2->position.x - obj1->position.x) , abs(obj2->position.y - obj1->position.y)};
	Vecf2 sum = { (obj2->width + obj1->width)/2.f, (obj2->height + obj1->height)/2.f };

	if (r.x < sum.x && r.y < sum.y)
	{

		return true;
	}

	return false;
}
