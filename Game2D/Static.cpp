#include "Static.h"
#include "Define.h"
#include "Texture.h"

Static::Static(SDL_Rect rect, const std::string & file, std::shared_ptr<Renderer> ren) :
	Object(0, 0, rect.w, rect.h, BLOCK_SIZE, 0, ren, file, Vecf2{ static_cast<float>(rect.x),static_cast<float>(rect.y) }, Vecf2{ 0.f, 0.f })
{
	clips.push_back(SDL_Rect{ 0,0,width, height });
}

Static::Static(const unsigned animation_delay, const std::vector<SDL_Rect> clips_, const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren) :
	Object(animation_delay, 0, clips_[0].w, clips_[0].h, static_cast<float>(clips_[0].w), 0, ren, file, position, Vecf2{ 0.f, 0.f })
{
		clips = clips_;
}

void Static::Draw(bool mirror)
{
	ren->Render(this, angle, mirror, scale);
}

void Static::Update(const float deltaTime)
{
	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;
}