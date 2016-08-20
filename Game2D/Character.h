#pragma once

#include "Object.h"

class Camera;

enum class States { OnFloor, Jumpe, Left, Right, Down, Up };

class Character :
	public Object
{
public:
	float mass;

	static std::vector<States> states;
	std::map<States, bool> key;

public:
	Character(const float x, const float y, const std::string &file, SDL_Renderer *ren);
	virtual ~Character();

	virtual void Update(const float DeltaTime) override;
};

