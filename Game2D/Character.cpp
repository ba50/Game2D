#include "Character.h"

#include "Inputs.h"
#include "Define.h"
#include "Texture.h"

#include "Bullet.h"
#include "Gameplay.h"
#include "Audio.h"

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

	delta_velocity = { 1e1f, 1e1f };
	max_velocity = 5e2f;
	mass = 1e2;

	collision_r = width;

	max_speed_x = false;
	max_speed_y = false;
}

Character::~Character()
{
	printf("Delete Character\n");
}

void Character::Update(const float deltaTime,
		std::vector<std::shared_ptr<Bullet>> &bullet_vector,
		std::shared_ptr<Audio> audio)
{
	//Inputs
	if (currentInput[Input::Up]) {
		if (!Gameplay::start) velocity.y = -max_velocity;
		Gameplay::start = true;
		useClip = 1;
		if (!max_speed_x) velocity.x = max_velocity*sinf(angle*PI / 180.f);
	
		else {
			velocity.x += delta_velocity.x*sinf(angle*PI / 180.f);
			if (abs(velocity.x) > max_velocity) max_speed_x = false;
		}

		if (!max_speed_y) {
			velocity.y = -max_velocity*cosf(angle*PI / 180.f);
		}
		else {
			velocity.y -= delta_velocity.y*cosf(angle*PI / 180.f);
			if (abs(velocity.y) > max_velocity) max_speed_y = false;
		}
		
		if (!max_speed_x && !max_speed_y) {
			delta_angle = 2.f;
		}
		else{
			delta_angle = 1.f;
		}
		printf("%f, %f: %f\n", velocity.x, velocity.y, velocity.Len());
	}
	else {
		max_speed_x = true;
		max_speed_y = true;
		useClip = 0;

		if (Gameplay::start) {
			velocity.y += 4.f;
			delta_angle = 6.f;
		}
	}

	if (currentInput[Input::Right]) {
		angle += delta_angle;
		if (angle > 180) {
			angle -= 360;
		}
	}

	if (currentInput[Input::Left]) {
		angle -= delta_angle;
		if (angle < -180) {
			angle += 360;
		}
	}

	if (currentInput[Input::Shot]) {
		if (bullet_trigger == 0) {
			bullet_vector.push_back(std::make_shared<Bullet>(position, angle, velocity, "Bullet.png", ren));
			audio->PlayExplosion();
			bullet_trigger = bullet_trigger_base;
		}
		bullet_trigger--;
	}

	if (position.y > 0) {
		if (angle < 0) angle += 10.f;
		if (angle > 0) angle -= 10.f;
	}

	if (position.y < -1000.f) {
		velocity.y = -max_velocity*cosf(2 * PI*(100.f+position.y));
	}

	if (Gameplay::start) {

		if (velocity.x > 0) velocity.x -= 1.f;
		if (velocity.x < 0) velocity.x += 1.f;

		if (velocity.y > 0) velocity.y -= 1.f;
		if (velocity.y < 0) velocity.y += 1.f;
	}

	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;
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
