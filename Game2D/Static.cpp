#include "Static.h"
#include "Define.h"
#include "Texture.h"

Static::Static(const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren) :
	Object(0, 0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0, ren, file, position, Vecf2{ 0.f, 0.f })
{
	clips.push_back(SDL_Rect{ 0,0,width, height });
}

Static::Static(SDL_Rect rect, const std::string & file, std::shared_ptr<Renderer> ren) :
	Object(0, 0, static_cast<float>(rect.h), static_cast<float>(rect.w), BLOCK_SIZE, 0, ren, file, Vecf2{ static_cast<float>(rect.x),static_cast<float>(rect.y) }, Vecf2{ 0.f, 0.f })
{
	clips.push_back(SDL_Rect{ 0,0,width, height });
}

Static::Static(const unsigned animation_delay, const std::vector<SDL_Rect> clips_, const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren) :
	Object(animation_delay, 0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0, ren, file, position, Vecf2{ 0.f, 0.f })
{
		clips = clips_;
}

void Static::Draw(bool mirror)
{
	ren->Render(this, angle, mirror);
}

void Static::Update()
{
	position = root_position;
}