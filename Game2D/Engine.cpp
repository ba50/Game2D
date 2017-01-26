#include "Engine.h"

Engine::Engine(
	const unsigned animation_delay,
	const float angle,
	const Vecf2 position,
	const std::string & file,
	const std::vector<SDL_Rect> clips,
	Renderer &ren
) : 
	Object(animation_delay, 0, clips[0].w, clips[0].h, angle, 0, file, clips, ren, position)
{}
