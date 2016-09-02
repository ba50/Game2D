#pragma once

#include <list>

#include "Object.h"

class Camera;

enum class States {OnFloor, CanFall, CanJumpe, DoJumpe, CanLeft, CanRight, Left, Right, Down, Up };

class Character :
	public Object
{
public:
	float mass;

	std::map<States, bool> currentStates;
	std::list<int> left, right, current;
	std::list<int>::iterator it;
	float timer;

public:
	Character(const float x, const float y, const std::string &file, SDL_Renderer *ren);
	virtual ~Character();

	virtual void Update(const float DeltaTime) override;
	void Inputs();
	void Collison(std::shared_ptr<Object> obj);
};

