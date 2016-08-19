#include "Static.h"
#include "Define.h"


Static::Static(const float x, const float y, const std::string & file, SDL_Renderer * ren)
{
	width = 64;
	height = 64;
	position.x = x;
	position.y = y;
	sprite = Texture::load(file, ren);

	if (sprite == nullptr)
		throw std::exception("shit!");

	SDL_Rect clipTemp;

	clipTemp.x = 0;
	clipTemp.y = 0;
	clipTemp.w = static_cast<int>(width);
	clipTemp.h = static_cast<int>(height);

	clips.push_back(clipTemp);
}

Static::~Static()
{
	cleanup(sprite);
}

void Static::Update(const float DeltaTime)
{
}
