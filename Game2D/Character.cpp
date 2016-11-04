#include "Character.h"

#include "Inputs.h"
#include "Define.h"
#include "Texture.h"

#include "Bullet.h"

std::vector<bool> Inputs::slope;

Character::Character(const float x, const float y, const std::string &file, std::shared_ptr<Renderer> & ren) :
	Object(ren),
	life(true),
	delta_angle(10)
{
	width = BLOCK_SIZE;
	height = BLOCK_SIZE;
	position.x = x;
	position.y = y;
	sprite = std::make_shared<Texture>(file, Object::ren);

	clips.push_back(SDL_Rect{ 0, 0, static_cast<int>(width), static_cast<int>(height) });


	Inputs::slope.push_back(false);
	Inputs::slope.push_back(false);
}

Character::~Character()
{
	printf("Delete Character\n");
}

void Character::Update(const float deltaTime)
{
	if (currentInput[Input::Right]) {
		angle += delta_angle;
		if (angle > 360) {
			angle -= 360;
		}
	}

	if (currentInput[Input::Left]) {
		angle -= delta_angle;
		if (angle < -360) {
			angle += 360;
		}
	}
}

void Character::Draw()
{
	ren->render(this, scale , angle);
}

void Character::Inputs()
{
	for (auto it = Inputs::key.begin(); it != Inputs::key.end(); ++it) {
		switch (it->first) {
		case Key::Up:
			switch (it->second)
			{
			case Action::Press:
				currentInput[Input::Up] = true;
				currentInput[Input::Down] = false;
				break;
			case Action::Release:
				currentInput[Input::Up] = false;
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Down:
			switch (it->second)
			{
			case Action::Press:
				currentInput[Input::Down] = true;
				currentInput[Input::Up] = false;
				break;
			case Action::Release:
				currentInput[Input::Down] = false;
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Right:
			switch (it->second)
			{
			case Action::Press:
				currentInput[Input::Right] = true;
				currentInput[Input::Left] = false;
				break;
			case Action::Release:
				currentInput[Input::Right] = false;
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Left:
			switch (it->second)
			{
			case Action::Press:
				currentInput[Input::Left] = true;
				currentInput[Input::Right] = false;
				break;
			case Action::Release:
				currentInput[Input::Left] = false;
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Z:
			switch (it->second)
			{
			case Action::Press:
				currentInput[Input::Jumpe] = true;
				break;
			case Action::Release:
				currentInput[Input::Jumpe] = false;
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::X:
			switch (it->second)
			{
			case Action::Press:
				currentInput[Input::Shot] = true;
				break;
			case Action::Release:
				currentInput[Input::Shot] = false;
				it->second = Action::Unknown;
				break;
			}
			break;
		}
	}
}

void Character::Collison()
{
}
