#include "Define.h"

#include "Inputs.h"
#include "Texture.h"
#include "Gameplay.h"
#include "Audio.h"

#include "Character.h"
#include "Bullet.h"

Character::Character(	

	const Vecf2 position,
	const std::string & file,
	const std::vector<SDL_Rect> clips,
	Renderer &ren
) :
	Moving(2, 0, 2, 255, 0, clips[0].w/2.f, position, file, clips, ren), 

	delta_angle(0.f),
	delta_velocity(5e1f),
	max_velocity(5e2f),
	recoil(0.f)
{
	//init engine
	std::vector<SDL_Rect> engine_clips;

	engine_clips.push_back(SDL_Rect{ 0,0,BLOCK_SIZE, BLOCK_SIZE });
	engine_clips.push_back(SDL_Rect{ BLOCK_SIZE,0,BLOCK_SIZE, BLOCK_SIZE });
	engine_clips.push_back(SDL_Rect{ 2*BLOCK_SIZE,0,BLOCK_SIZE, BLOCK_SIZE });
	engine_clips.push_back(SDL_Rect{ 3*BLOCK_SIZE,0,BLOCK_SIZE, BLOCK_SIZE });

	engine = std::make_unique<Engine>(3, angle, position, "Source/Engine.png", engine_clips, ren);
}

void Character::Update(const float deltaTime)
{
	//Inputs
	if (currentInput[Input::Boost]) {
		engine->Animation(1, 3);
		if (!Gameplay::start) velocity.y = -max_velocity;
		Gameplay::start = true;

		//acceleration
		velocity.x += delta_velocity*sinf(angle*PI / 180.f);
		velocity.y -= delta_velocity*cosf(angle*PI / 180.f);

		//clumping velocity
		float len = velocity.Len();
		velocity = velocity.Norm()*std::min(max_velocity, len);

		//gravity
		if (position.y <= 0) velocity.y += 2.f;
		delta_angle = 2.f;

	}
	else {
		engine->useClip = 0;
		if (Gameplay::start) {
			Gameplay::pausa = false;

			//gravity
			if (position.y <= 0) velocity.y += 6.f;
			delta_angle = 6.f;
		}
	}

	if (currentInput[Input::Right]) {
		angle += delta_angle;
		if (angle > 360) {
			angle -= 360;
		}
	}

	if (currentInput[Input::Left]) {
		angle -= delta_angle;
		if (angle < 0) {
			angle += 360;
		}
	}

	if (currentInput[Input::Shot]) {
		if (bullet_trigger == 0) {
			shoot = true;
			bullet_trigger = bullet_trigger_base;
			if (recoil < 10.f)
				recoil += 1.1f;
		}
		bullet_trigger--;
	}
	else {
		recoil = 0.f;
	}

	//Sky
	if (position.y < Gameplay::sky_level)
		velocity.y -= 1.f*(position.y - Gameplay::sky_level);

	//Water
	if (position.y > Gameplay::water_level) {
		if (angle > 45.f && angle <= 180.f) angle -= 10.f;
		if (angle < 315.f && angle > 180.f) angle += 10.f;
		velocity.y -= 20.f;
		health -= 5;
	}

	useClip = static_cast<int>(std::floorf(angle*clips.size() / 360.f));
	if (useClip >= clips.size()) useClip = 0;

	if (health < MAX_HEALTH) {
		health += 1;
	}

	printf("%d\n", health);

	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;

	engine->position = position;

	engine->position.x -= 1.f*BLOCK_SIZE*Renderer::scale.x*sinf(angle*PI / 180.f);
	engine->position.y += 1.f*BLOCK_SIZE*Renderer::scale.y*cosf(angle*PI / 180.f);

	engine->angle = angle;
}

void Character::Inputs()
{
	for (auto it = Inputs::key.begin(); it != Inputs::key.end(); ++it) {
		switch (it->first) {
		case Key::Up:
			switch (it->second)
			{
			case Action::Press:
				currentInput[Input::Boost] = true;
				break;
			case Action::Release:
				currentInput[Input::Boost] = false;
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Right:
			switch (it->second)
			{
			case Action::Press:
				currentInput[Input::Right] = true;
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
				break;
			case Action::Release:
				currentInput[Input::Left] = false;
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

void Character::Collison(Object &obj)
{
	if (sqrtf(
		(obj.position.x - position.x)*(obj.position.x - position.x) +
		(obj.position.y - position.y)*(obj.position.y - position.y)) <
		(obj.collision_r / 4.f + collision_r / 4.f))
	{
		if (health > 128) {
			health -= 50;
		}
		Camera::Shake();
	}
}
