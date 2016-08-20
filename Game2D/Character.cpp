#include "Character.h"

#include "Define.h"
#include "Camera.h"

std::vector<States> Character::states;
std::vector<bool> Inputs::slope;

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

	Character::states.reserve(500);
	Inputs::slope.push_back(false);
	Inputs::slope.push_back(false);
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


	//Inputs
	for (auto it = Inputs::key.begin(); it != Inputs::key.end(); ++it) {
		switch (it->first) {
		case Key::Up:
			switch (it->second)
			{
			case Action::Press:
				break;
			case Action::Release:
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Down:
			switch (it->second)
			{
			case Action::Press:
				break;
			case Action::Release:
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Right:
			switch (it->second)
			{
			case Action::Press:
				velocity.x += 25;
				break;
			case Action::Release:
				velocity.x = 0.1;
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Left:
			switch (it->second)
			{
			case Action::Press:
				velocity.x -= 25;
				break;
			case Action::Release:
				velocity.x = -0.1;
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Space:
				switch (it->second)
				{
				case Action::Press:
					if (velocity.x >= 0) {
						useClip = 5;
					}
					else {
						useClip = 4;
					}
					break;
				case Action::Release:
					velocity.y = -100;
					it->second = Action::Unknown;
					break;
				}
			break;
		}
	}

	Character::states.clear();

	position.x += velocity.x*DeltaTime;
	position.y += velocity.y*DeltaTime;
}
