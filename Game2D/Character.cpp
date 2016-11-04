#include "Character.h"

#include "Inputs.h"
#include "Define.h"
#include "Texture.h"

#include "Bullet.h"

std::vector<bool> Inputs::slope;

Character::Character(const float x, const float y, const std::string &file, std::shared_ptr<Renderer> & ren) :
	Object(ren),
	life(true),
	delta_angle(10),
	bullet_trigger_base(2),
	bullet_trigger(2)
{
	width = BLOCK_SIZE;
	height = BLOCK_SIZE;
	position.x = x;
	position.y = y;
	sprite = std::make_shared<Texture>(file, Object::ren);

	clips.push_back(SDL_Rect{ 0, 0, static_cast<int>(width), static_cast<int>(height) });

	Inputs::slope.push_back(false);
	Inputs::slope.push_back(false);


	mass = 1000.f;
	delta_velocity = { 50.f, 50.f };

}

Character::~Character()
{
	printf("Delete Character\n");
}

void Character::Update(const float deltaTime, std::vector<std::shared_ptr<Bullet>> &bullet_vector)
{
	//Inputs
	if (currentInput[Input::Up]) {
		velocity.x += delta_velocity.x*sinf(PI*angle / 180.f);
		velocity.y -= delta_velocity.y*cosf(PI*angle / 180.f);
	}

	if (currentInput[Input::Down]) {
		velocity.x -= delta_velocity.x*sinf(PI*angle / 180.f);
		velocity.y += delta_velocity.y*cosf(PI*angle / 180.f);
	}

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

	if (currentInput[Input::Shot]) {
		if (bullet_trigger == 0) {
			bullet_vector.push_back(std::make_shared<Bullet>(position, angle, velocity, "Bullet.png", ren));
			bullet_trigger = bullet_trigger_base;
		}
		bullet_trigger--;
	}

	//Physic

	if (position.y < 0) {
		velocity.y += .2f*sqrtf(abs(2.f*g*position.y));
	}
	else {
		velocity.y -= sqrtf(abs(2.f*g*position.y));
	}

	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;
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
