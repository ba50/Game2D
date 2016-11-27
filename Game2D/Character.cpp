#include "Define.h"

#include "Inputs.h"
#include "Texture.h"
#include "Gameplay.h"
#include "Audio.h"

#include "Character.h"
#include "Bullet.h"
#include "Static.h"

std::vector<bool> Inputs::slope;

Character::Character(const Vecf2 position, const std::string &file, std::shared_ptr<Renderer> & ren) :
	Object(0, 0, 2 * BLOCK_SIZE, 2 * BLOCK_SIZE, 2*BLOCK_SIZE, 0, ren, file, position, Vecf2{ 0.f, 0.f }),
	life(true),
	delta_angle(0.f),
	delta_velocity(5e1),
	max_velocity(5e2f),
	health(10.f),
	bullet_trigger_base(9),
	bullet_trigger(9)
{
	for (int i = 0; i < 36; i++) {
		clips.push_back(SDL_Rect{ i*2*BLOCK_SIZE, 0, 2 * BLOCK_SIZE, 2 * BLOCK_SIZE });
	}

	Inputs::slope.push_back(false);
	Inputs::slope.push_back(false);

	//init engine
	std::vector<SDL_Rect> engine_clips;

	engine_clips.push_back(SDL_Rect{ 0,0,BLOCK_SIZE, BLOCK_SIZE });
	engine_clips.push_back(SDL_Rect{ BLOCK_SIZE,0,BLOCK_SIZE, BLOCK_SIZE });
	engine_clips.push_back(SDL_Rect{ 2*BLOCK_SIZE,0,BLOCK_SIZE, BLOCK_SIZE });
	engine_clips.push_back(SDL_Rect{ 3*BLOCK_SIZE,0,BLOCK_SIZE, BLOCK_SIZE });

	engine = std::make_unique<Static>(5, engine_clips, position, "Engine.png", ren);
}

void Character::Update(const float deltaTime,
	std::vector<std::shared_ptr<Bullet>> &bullet_vector,
	std::shared_ptr<Audio> audio)
{


	//Box
	if (position.y >= WATER_LEVEL + 500 ||
		position.y <= SKY_LEVEL - 1000) velocity.y = 0;

		engine->Animation(1, 3);
	//Inputs
	if (currentInput[Input::Up]) {
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
		delta_angle = 3.f;
	}
	else {
		engine->useClip = 0;
		if (Gameplay::start) {

//			velocity = Vecf2{ 0.f,0.f };

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
			Vecf2 position_temp{ position.x + 1.1f*BLOCK_SIZE*sinf(angle*PI / 180.f), position.y - 1.1f*BLOCK_SIZE*cosf(angle*PI / 180.f) };
			bullet_vector.push_back(std::make_shared<Bullet>(angle+Math::Rand(-5.f,5.f), velocity, position_temp, "Bullet.png", ren));
			audio->PlayExplosion();
			bullet_trigger = bullet_trigger_base;
		}
		bullet_trigger--;
	}

	//Sky
	if (position.y < SKY_LEVEL)
		velocity.y -= 1.f*(position.y - SKY_LEVEL);

	//Water
	if (position.y > WATER_LEVEL) {
		if (angle > 45.f && angle <= 180.f) angle -= 10.f;
		if (angle < 315.f && angle > 180.f) angle += 10.f;
		velocity.y -= 20.f;
	}

	drawing_angle = angle - std::floorf(angle / 10.f) * 10.f;

	useClip = static_cast<int>(std::floorf(angle / 10.f));
	if (useClip < 0 || useClip > 35) useClip = 0;
	

	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;

	engine->position = position;

	engine->position.x -= 1.4f*BLOCK_SIZE*sinf(angle*PI / 180.f);
	engine->position.y += 1.4f*BLOCK_SIZE*cosf(angle*PI / 180.f);

	engine->angle = angle;
}

void Character::Draw()
{
	ren->render(this, scale, drawing_angle);
	engine->Draw();
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
