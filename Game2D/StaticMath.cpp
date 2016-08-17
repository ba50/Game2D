#include "StaticMath.h"

#include "Object.h"

void StaticMath::logSDLError(std::ostream &os, const std::string &msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}

bool StaticMath::collison(const Object  *obj1, const Object *obj2)
{
	float r = sqrt(pow(obj2->pos.x - obj1->pos.x, 2) + pow(obj2->pos.y - obj1->pos.y, 2));
	float sum = obj2->radius + obj1->radius;
	if (r < sum) {
		return true;
	}
	return false;

}