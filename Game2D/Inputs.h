#pragma once

#include <queue>
#include <map>

#include <SDL.h>

enum class KeyDown {Up, Down, Right, Left, Jump};
enum class KeyUp { Up, Down, Right, Left, Jump };

class Inputs 
{
public:
	static std::queue<int> events;
	static std::map<int, KeyUp> keyup;
	static std::map<int, KeyDown> keydown;

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
					events.push(SDLK_UP);
					break;
				case SDLK_DOWN:
					events.push(SDLK_DOWN);
					break;
				case SDLK_RIGHT:
					events.push(SDLK_RIGHT);
					break;
				case SDLK_LEFT:
					events.push(SDLK_LEFT);
					break;
				case SDLK_SPACE:
					events.push(SDLK_SPACE);
					break;
				case SDLK_ESCAPE:
					return true;
					break;
				default:
					break;
				}
			}
			if (e.type == SDL_KEYUP) {

				switch (e.key.keysym.sym) {
				case SDLK_UP:
					events.push(SDLK_UP);
					break;
				case SDLK_DOWN:
					events.push(SDLK_DOWN);
					break;
				case SDLK_RIGHT:
					events.push(SDLK_RIGHT);
					break;
				case SDLK_LEFT:
					events.push(SDLK_LEFT);
					break;
				case SDLK_SPACE:
					events.push(SDLK_SPACE);
					break;
				case SDLK_ESCAPE:
					return true;
					break;
				default:
					break;
				}
			}
		}

		return false;
	}
};