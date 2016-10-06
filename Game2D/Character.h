#pragma once

#include <list>
#include <map>

#include "Object.h"

class Bullet;

class Character :
	public Object
{
public:
	Vecf2 velocityMax;

	enum class States { InAir, OnFloor, CanFall, CanJumpe, CanLeft, CanRight, Left, Right, Down, UpLeft, UpRight };
	enum class Input { Shot, Jumpe, Left, Right, Down, Up };

	std::map<States, bool> currentStates;
	std::map<Input, bool> currentInput;

	std::list<int> leftAnimation, rightAnimation, upLeftAnimation, upRightAnimation, currentAnimation;
	std::list<int>::iterator itAnimation;
	float animationTimer, bulletTimer;

	std::list<std::shared_ptr<Bullet>> bulletList;

	bool life;
	Vecf2 newPosition;

public:
	Character(const float x, const float y, const std::string &file, std::shared_ptr<Renderer> & ren);
	~Character();

	void Update(const float deltaTime) override;
	void Draw() override;
	void Inputs();
	void Collison(std::shared_ptr<Object> obj);
};