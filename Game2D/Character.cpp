#include "Character.h"

#include "Define.h"
#include "Camera.h"

std::vector<States> Character::states;

Character::Character(const float x, const float y, const std::string &file, SDL_Renderer *ren) :
	mass(100)
{
	width = 80;
	height = 48;
	position.x = x;
	position.y = y;
	sprite = Texture::load(file, ren);

	if (sprite == nullptr)
		throw std::exception("shit!");

	SDL_Rect clipTemp;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
			clipTemp.x = i * static_cast<int>(width);
			clipTemp.y = j * static_cast<int>(height);
			clipTemp.w = static_cast<int>(width);
			clipTemp.h = static_cast<int>(height);

			clips.push_back(clipTemp);
		}
	}

	Inputs::keydown[SDLK_UP] = KeyDown::Up;
	Inputs::keydown[SDLK_DOWN] = KeyDown::Down;
	Inputs::keydown[SDLK_RIGHT] = KeyDown::Right;
	Inputs::keydown[SDLK_LEFT] = KeyDown::Left;
	Inputs::keydown[SDLK_SPACE] = KeyDown::Jump;

	Character::states.reserve(500);
}

Character::~Character()
{
	cleanup(sprite);
}

void Character::Update(const float DeltaTime)
{

	if (states.empty())
	{
		velocity.y += 1;

		if (velocity.x > 0) {
			useClip = 3;
		}
		else
		{
			useClip = 2;
		}
		
	}
	else
	{
		velocity.y = 0;

		if (velocity.x > 0) {
			useClip = 1;
		}
		else
		{
			useClip = 0;
		}
	}

	Character::states.clear();

	//Inputs
	for (size_t i = 0; i < Inputs::events.size(); i++) {
		switch (Inputs::keydown[Inputs::events.back()]) {
		case KeyDown::Right:
			velocity.x = 100;
			break;
		case KeyDown::Left:
			velocity.x = -100;
			break;
		case KeyDown::Jump:
			useClip = 4;
			break;
		}
		Inputs::events.pop();
	}

	position.x += velocity.x*DeltaTime;
	position.y += velocity.y*DeltaTime;
}
