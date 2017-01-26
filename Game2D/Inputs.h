#pragma once

#include <map>
#include <vector>

#include <SDL.h>

enum class Key { Up, Down, Right, Left, Z, X };
enum class Action { Press, Release, Unknown };

class Inputs
{
	static SDL_Event event;

public:
	static std::map<Key, Action> key;
	static std::vector<bool> slope;

public:
	static void Update(bool &quit);

};
