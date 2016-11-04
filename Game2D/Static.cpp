#include "Static.h"
#include "Define.h"
#include "Texture.h"

Static::Static(const Vecf2 position, const std::string & file, std::shared_ptr<Renderer> ren, bool collidable) :
	Object(ren)
{
	width = BLOCK_SIZE;
	height = BLOCK_SIZE;
	Object::position = position;
	sprite = std::make_shared<Texture>(file, ren);
	Object::collidable = collidable;

	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });

}

Static::Static(SDL_Rect rect, const std::string & file, std::shared_ptr<Renderer> ren) :
	Object(ren)
{
	position.x = static_cast<float>(rect.x);
	position.y = static_cast<float>(rect.y);
	width = static_cast<float>(rect.w);
	height = static_cast<float>(rect.h);
	sprite = std::make_shared<Texture>(file, ren);

	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });
}

Static::~Static()
{

}

void Static::Update(const float deltaTime)
{
}

void Static::Draw()
{
	ren->render(this);
}
