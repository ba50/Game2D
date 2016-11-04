#include "Character.h"

#include "Inputs.h"
#include "Define.h"
#include "Texture.h"

#include "Bullet.h"
#include "Gameplay.h"

std::vector<bool> Inputs::slope;

Character::Character(const float x, const float y, const std::string &file, std::shared_ptr<Renderer> & ren) :
	Object(ren),
	life(true),
	delta_angle(0.f),
	bullet_trigger_base(5),
	bullet_trigger(5)
{
	width = 2*BLOCK_SIZE;
	height = 2*BLOCK_SIZE;
	position.x = x;
	position.y = y;
	sprite = std::make_shared<Texture>(file, Object::ren);

	clips.push_back(SDL_Rect{ 0, 0, static_cast<int>(width), static_cast<int>(height) });
	clips.push_back(SDL_Rect{ 0, static_cast<int>(height), static_cast<int>(width), static_cast<int>(height) });

	Inputs::slope.push_back(false);
	Inputs::slope.push_back(false);

	mass = 1e3f;
	delta_force = { 4e5f, 4e5f };
	force = { 0.f,0.f };
	max_momentum = { 4e5f, 4e5f };
	newPosition = position;

	collision_r = width;
}

Character::~Character()
{
	printf("Delete Character\n");
}

void Character::Update(const float deltaTime, std::vector<std::shared_ptr<Bullet>> &bullet_vector)
{
	//Inputs
	if (currentInput[Input::Up]) {
		useClip = 1;
		force.x = delta_force.x*sinf(PI*angle / 180.f);
		force.y = -delta_force.y*cosf(PI*angle / 180.f);
		if(position.y >0) force.y -= 1e3f*mass*g;
		if(position.y < -3000) force.y += 1e3f*mass*g;
		delta_angle = 1.7f;
	}
	else {
		useClip = 0;
		force.x = 0.f;
		if (position.y < 0) force.y += .2e1f*mass*g;
		if(position.y >0) force.y -= 1e1f*mass*g;
		delta_angle = 5.f;
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

	momentum.x += force.x*deltaTime / 2.f;
	newPosition.x += momentum.x*deltaTime / mass;
	momentum.x += force.x*deltaTime / 2.f;

	momentum.y += force.y*deltaTime / 2.f;
	newPosition.y += momentum.y*deltaTime / mass;
	momentum.y += force.y*deltaTime / 2.f;

	velocity.x = momentum.x / mass;
	velocity.y = momentum.y / mass;

	if (momentum.x > max_momentum.x) momentum.x = max_momentum.x;
	if (momentum.x < -max_momentum.x) momentum.x = -max_momentum.x;

	if (momentum.y > max_momentum.y) momentum.y = max_momentum.y;
	if (momentum.y < -max_momentum.y) momentum.y = -max_momentum.y;

	

	position = newPosition;
}

void Character::Draw()
{
	ren->render(this, scale, angle);
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

void Character::Collison(std::shared_ptr<Object> obj)
{
	if (sqrtf(
		(obj->position.x - position.x)*(obj->position.x - position.x) +
		(obj->position.y - position.y)*(obj->position.y - position.y)) <
		(obj->collision_r / 4.f + collision_r / 4.f)) {
		health -= 1.5;
		if (health <= 0.f) {
			life = false;
		}
		ren->camera->Shake();
		Gameplay::slow_motion = true;
	}
}
