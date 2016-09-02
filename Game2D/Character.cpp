#include "Character.h"

#include "Define.h"
#include "Camera.h"

std::vector<bool> Inputs::slope;

Character::Character(const float x, const float y, const std::string &file, SDL_Renderer *ren) :
	mass(100)
{
	width = 64;
	height = 64;
	position.x = x;
	position.y = y;
	sprite = Texture::load(file, ren);

	if (sprite == nullptr)
		throw std::exception("shit!");

	SDL_Rect clipTemp;
	for (int i = 0; i < 11; ++i) {
		for (int j = 0; j < 2; ++j) {
			clipTemp.x = i * static_cast<int>(width);
			clipTemp.y = j * static_cast<int>(height);
			clipTemp.w = static_cast<int>(width);
			clipTemp.h = static_cast<int>(height);

			clips.push_back(clipTemp);
		}
	}

	Inputs::slope.push_back(false);
	Inputs::slope.push_back(false);

	collisionBoxX.x = (width-18) / 2;
	collisionBoxX.y = (height - 25) / 2;

	collisionBoxY.x = (width - 25) / 2;
	collisionBoxY.y = (height-20) / 2;

	currentStates[States::Down] = false;
	currentStates[States::Up] = false;
	currentStates[States::Left] = false;
	currentStates[States::Right] = false;

	timer = 0;

	left.push_back(0);
	left.push_back(2);
	left.push_back(4);

	right.push_back(1);
	right.push_back(3);
	right.push_back(5);

	current = right;
	it = current.begin();

}

Character::~Character()
{
	cleanup(sprite);
}

void Character::Update(const float deltaTime)
{
	velocity.y += 10;

	if (!currentStates[States::CanJumpe]) {
		velocity.y = 0;
		position.y++;
	}
	if (!currentStates[States::CanFall]) {
		velocity.y = 0;
	}

	if (currentStates[States::Right]) {
		velocity.x = 400;
		current=right;
	}
	else if (currentStates[States::Left]) {
		velocity.x = -400;
		current = left;
	}
	else {
		if (velocity.x > 10 && currentStates[States::CanRight]) {
			velocity.x -= 50;
		}
		else if (velocity.x < -10 && currentStates[States::CanLeft]) {
			velocity.x += 50;
		}
		else {
			velocity.x = 0;
		}
	}

	if (currentStates[States::DoJumpe] && currentStates[States::OnFloor]) {
		velocity.y = -400;
		currentStates[States::DoJumpe] = false;
	}

	if (timer >= 0.1f && velocity.x !=0 && currentStates[States::OnFloor]) {
		timer = 0.f;
		++it;
	}

	if (it == current.end()) {
		it = current.begin();
	}

	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;

	currentStates[States::CanJumpe] = true;
	currentStates[States::CanFall] = true;
	currentStates[States::CanLeft] = true;
	currentStates[States::CanRight] = true;
	currentStates[States::OnFloor] = false;

	timer += deltaTime;
	useClip = *it;

}

void Character::Inputs()
{
	for (auto it = Inputs::key.begin(); it != Inputs::key.end(); ++it) {
		switch (it->first) {
		case Key::Up:
			switch (it->second)
			{
			case Action::Press:
				currentStates[States::Up] = true;
				currentStates[States::Down] = false;
				break;
			case Action::Release:
				currentStates[States::Up] = false;
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Down:
			switch (it->second)
			{
			case Action::Press:
				currentStates[States::Down] = true;
				currentStates[States::Up] = false;
				break;
			case Action::Release:
				currentStates[States::Down] = false;
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Right:
			switch (it->second)
			{
			case Action::Press:
				currentStates[States::Right] = true;
				currentStates[States::Left] = false;
				break;
			case Action::Release:
				currentStates[States::Right] = false;
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Left:
			switch (it->second)
			{
			case Action::Press:
				currentStates[States::Left] = true;
				currentStates[States::Right] = false;
				break;
			case Action::Release:
				currentStates[States::Left] = false;
				it->second = Action::Unknown;
				break;
			}
			break;
		case Key::Space:
			switch (it->second)
			{
			case Action::Press:
				currentStates[States::DoJumpe] = false;
				break;
			case Action::Release:
				currentStates[States::DoJumpe] = true;
				it->second = Action::Unknown;
				break;
			}
			break;
		}
	}
}

void Character::Collison(std::shared_ptr<Object> obj)
{
	if ((position.x - collisionBoxY.x) < (obj->position.x + obj->collisionBox.x) &&
		(position.x + collisionBoxY.x) > (obj->position.x - obj->collisionBox.x) &&
		((position.y - collisionBoxY.y) - 4.f) < ((obj->position.y + obj->collisionBox.y) + 4.f) &&
		((position.y - collisionBoxY.y) + 4.f) > ((obj->position.y + obj->collisionBox.y) - 4.f)) {
		currentStates[States::CanJumpe] = false;
	}

	if ((position.x - collisionBoxY.x) < (obj->position.x + obj->collisionBox.x) &&
		(position.x + collisionBoxY.x) > (obj->position.x - obj->collisionBox.x) &&
		((position.y + collisionBoxY.y) - 4.f) < ((obj->position.y - obj->collisionBox.y) + 4.f) &&
		((position.y + collisionBoxY.y) + 4.f) > ((obj->position.y - obj->collisionBox.y) - 4.f)) {
		currentStates[States::CanFall] = false;
		currentStates[States::OnFloor] = true;
	}

	if (((position.x - collisionBoxX.x) - 4.f) < ((obj->position.x + obj->collisionBox.x) + 4.f) &&
		((position.x - collisionBoxX.x) + 4.f) > ((obj->position.x + obj->collisionBox.x) - 4.f) &&
		(position.y - collisionBoxX.y) < (obj->position.y + obj->collisionBox.y) &&
		(position.y + collisionBoxX.y) > (obj->position.y - obj->collisionBox.y)) {
		currentStates[States::CanLeft] = false;
		currentStates[States::Left] = false;
	}

	if (((position.x + collisionBoxX.x) - 4.f) < ((obj->position.x - obj->collisionBox.x) + 4.f) &&
		((position.x + collisionBoxX.x) + 4.f) > ((obj->position.x - obj->collisionBox.x) - 4.f) &&
		(position.y - collisionBoxX.y) < (obj->position.y + obj->collisionBox.y) &&
		(position.y + collisionBoxX.y) > (obj->position.y - obj->collisionBox.y)) {
		currentStates[States::CanRight] = false;
		currentStates[States::Right] = false;
	}

}
