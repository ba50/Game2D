#include "Static.h"
#include "Define.h"
#include "Texture.h"

Static::Static(const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren) :
	Object(0, BLOCK_SIZE, BLOCK_SIZE, width, 0, ren, file, position, Vecf2{ 0.f, 0.f })
{
	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });
}

Static::Static(SDL_Rect rect, const std::string & file, std::shared_ptr<Renderer> ren) :
	Object(0, static_cast<float>(rect.h), static_cast<float>(rect.w), width, 0, ren, file, Vecf2{ static_cast<float>(rect.x),static_cast<float>(rect.y) }, Vecf2{ 0.f, 0.f })
{
	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });
}

Static::Static(const std::vector<SDL_Rect> clips_, const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren) :
	Object(0, BLOCK_SIZE, BLOCK_SIZE, width, 0, ren, file, position, Vecf2{ 0.f, 0.f })
{
		clips = clips_;
}

void Static::Draw()
{
	ren->render(this);
}
