#include "Static.h"
#include "Define.h"
#include "Texture.h"

Static::Static(const float x, const float y, const std::string & file, std::shared_ptr<Renderer> ren)
{
	width = BLOCK_SIZE;
	height = BLOCK_SIZE;
	position.x = x;
	position.y = y;
	sprite = std::make_shared<Texture>(file, ren);

	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });

	collisionBox.x = width / 2;
	collisionBox.y = height / 2;
}

Static::Static(SDL_Rect rect, const std::string & file, std::shared_ptr<Renderer> ren)
{
	position.x = static_cast<float>(rect.x);
	position.y = static_cast<float>(rect.y);
	width = static_cast<float>(rect.w);
	height = static_cast<float>(rect.h);
	sprite = std::make_shared<Texture>(file, ren);

	clips.push_back(SDL_Rect{ 0,0,static_cast<int>(width), static_cast<int>(height) });

	collisionBox.x = width / 2;
	collisionBox.y = height / 2;

}

Static::~Static()
{

}

void Static::Update(const float deltaTime)
{
}
