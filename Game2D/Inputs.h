#pragma once

#include <map>

#include <SDL.h>

enum class Key { Up, Down, Right, Left, Space, LShift };
enum class Action { Press, Release, Unknown };

class Inputs
{
public:
	static std::map<Key, Action> key;
	static std::vector<bool> slope;

public:
	static bool Update()
	{
		SDL_Event e;
		//Event Polling
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return true;
			}
			//Use number input to select which clip should be drawn
			if (e.type == SDL_KEYDOWN) {

				switch (e.key.keysym.sym) {
				case SDLK_UP:
					slope[0] = true;
					break;
				case SDLK_DOWN:
					slope[0] = true;
					break;
				case SDLK_RIGHT:
					slope[0] = true;
					break;
				case SDLK_LEFT:
					slope[0] = true;
					break;
				case SDLK_SPACE:
					slope[0] = true;
					break;
				case SDLK_LSHIFT:
					slope[0] = true;
					break;
				case SDLK_ESCAPE:
					return true;
					break;
				}
			}
			if (e.type == SDL_KEYUP) {

				switch (e.key.keysym.sym) {
				case SDLK_UP:
					slope[0] = false;
					slope[1] = true;
					break;
				case SDLK_DOWN:
					slope[0] = false;
					slope[1] = true;
					break;
				case SDLK_RIGHT:
					slope[0] = false;
					slope[1] = true;
					break;
				case SDLK_LEFT:
					slope[0] = false;
					slope[1] = true;
					break;
				case SDLK_SPACE:
					slope[0] = false;
					slope[1] = true;
					break;
				case SDLK_LSHIFT:
					slope[0] = false;
					slope[1] = true;
					break;
				}
			}

			switch (e.key.keysym.sym) {
			case SDLK_UP:
				if (slope[0] && !slope[1]) {
					key[Key::Up] = Action::Press;
				}
				if (!slope[0] && slope[1]) {
					key[Key::Up] = Action::Release;
				}
				break;
			case SDLK_DOWN:
				if (slope[0] && !slope[1]) {
					key[Key::Down] = Action::Press;
				}
				if (!slope[0] && slope[1]) {
					key[Key::Down] = Action::Release;
				}
				break;
			case SDLK_RIGHT:
				if (slope[0] && !slope[1]) {
					key[Key::Right] = Action::Press;
				}
				if (!slope[0] && slope[1]) {
					key[Key::Right] = Action::Release;
				}
				break;
			case SDLK_LEFT:
				if (slope[0] && !slope[1]) {
					key[Key::Left] = Action::Press;
				}
				if (!slope[0] && slope[1]) {
					key[Key::Left] = Action::Release;
				}
				break;
			case SDLK_SPACE:
				if (slope[0] && !slope[1]) {
					key[Key::Space] = Action::Press;
				}
				if (!slope[0] && slope[1]) {
					key[Key::Space] = Action::Release;
				}
				break;
			case SDLK_LSHIFT:
				if (slope[0] && !slope[1]) {
					key[Key::LShift] = Action::Press;
				}
				if (!slope[0] && slope[1]) {
					key[Key::LShift] = Action::Release;
				}
				break;
			case SDLK_ESCAPE:
				return true;
				break;
			}
		}
		slope[0] = false;
		slope[1] = false;
		return false;
	}
};