#pragma once
#include "Object.h" 

#include <map>

class Character;

class Enemy :
	public Object
{
public:
	enum class States {Detect};
	std::map<States, bool> currentStates;
	unsigned int counter;

public:
	Enemy(const float x, const float y, const std::string & file, std::shared_ptr<Renderer> ren);
	~Enemy();

	void Update(const float deltaTime) override;
	void Detect(std::shared_ptr<Character> cha);

	void Collision(std::shared_ptr<Object> obj);
};

