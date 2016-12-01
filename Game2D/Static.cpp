#include "Static.h"
#include "Define.h"
#include "Texture.h"

Static::Static(
	const unsigned animation_delay, 
	const std::vector<SDL_Rect> clips_, 
	const Vecf2 position,
	const std::string & file,
	Renderer &ren
) :
	Object(animation_delay, 0, clips_[0].w, clips_[0].h, 0, file, ren, position)
{
		clips = clips_;
}

void Static::Draw(Renderer &ren, bool reflection)
{
	ren.Render(*this, angle, reflection, scale);
}