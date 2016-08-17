#pragma once

#include <queue>

#include <SDL.h>

#include "Object.h"

class Inputs 
{
public:
	static std::vector<int> events;

public:
	static bool Update(Object *obj)
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
//					events.push_back(SDLK_UP);
					obj->useClip = 0;
					obj->momentum.y -= 1;
					break;
				case SDLK_DOWN:
//					events.push(SDLK_DOWN);
					obj->useClip = 1;
					obj->momentum.y += 1;
					break;
				case SDLK_RIGHT:
//					events.push(SDLK_RIGHT);
					obj->useClip = 2;
					obj->momentum.x += 1;
					break;
				case SDLK_LEFT:
//					events.push(SDLK_LEFT);
					obj->useClip = 3;
					obj->momentum.x -= 1;
					break;
				case SDLK_ESCAPE:
//					events.push(SDLK_ESCAPE);
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