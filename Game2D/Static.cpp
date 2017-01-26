#include "Static.h"

Static::Static(
		const Vecf2 position, 
		const std::string & file,
		const std::vector<SDL_Rect> clips,
		Renderer &ren
) :
	Object(0, 0, clips[0].w, clips[0].h, 0, 0, file, clips, ren, position)
{}
