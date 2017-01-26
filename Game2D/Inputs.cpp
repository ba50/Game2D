#include "Inputs.h"

void Inputs::Update(bool &quit)
{
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		quit = true;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
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
		case SDLK_z:
			slope[0] = true;
			break;
		case SDLK_x:
			slope[0] = true;
			break;
		case SDLK_ESCAPE:
			quit = true;
			break;
		}
		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
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
		case SDLK_z:
			slope[0] = false;
			slope[1] = true;
			break;
		case SDLK_x:
			slope[0] = false;
			slope[1] = true;
			break;
		case SDLK_ESCAPE:
			quit = true;
			break;
		}
		break;

	}

	switch (event.key.keysym.sym) {
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
	case SDLK_z:
		if (slope[0] && !slope[1]) {
			key[Key::Z] = Action::Press;
		}
		if (!slope[0] && slope[1]) {
			key[Key::Z] = Action::Release;
		}
		break;

	case SDLK_x:
		if (slope[0] && !slope[1]) {
			key[Key::X] = Action::Press;
		}
		if (!slope[0] && slope[1]) {
			key[Key::X] = Action::Release;
		}
		break;
	}


	slope[0] = false;
	slope[1] = false;
}

SDL_Event Inputs::event;
std::vector<bool> Inputs::slope;