#include "Character.h"

#include "Define.h"
#include "Camera.h"
#include "Texture.h"
#include "Inputs.h"
#include "Bullet.h"

#include "Renderer.h"

std::vector<bool> Inputs::slope;

Character::Character(const float x, const float y, const std::string &file, std::shared_ptr<Renderer> & ren) :
	ren(ren)
{
	width = BLOCK_SIZE;
	height = BLOCK_SIZE;
	position.x = x;
	position.y = y;
	velocityMax = Vecf2{ 400.f,350.f };
	sprite = std::make_shared<Texture>(file, ren);

	for (int i = 0; i < 11; ++i) {
		for (int j = 0; j < 2; ++j) {

			clips.push_back(SDL_Rect{ i * static_cast<int>(width), j * static_cast<int>(height), static_cast<int>(width), static_cast<int>(height) });

		}
	}

	Inputs::slope.push_back(false);
	Inputs::slope.push_back(false);

	collisionBoxX.x = (width-18) / 2;
	collisionBoxX.y = (height - 25) / 2;

	collisionBoxY.x = (width - 25) / 2;
	collisionBoxY.y = (height-20) / 2;

	animationTimer = 0;
	bulletTimer = 0;

	leftAnimation.push_back(0);
	leftAnimation.push_back(2);
	leftAnimation.push_back(4);

	rightAnimation.push_back(1);
	rightAnimation.push_back(3);
	rightAnimation.push_back(5);

	upLeftAnimation.push_back(6);
	upLeftAnimation.push_back(8);
	upLeftAnimation.push_back(10);

	upRightAnimation.push_back(7);
	upRightAnimation.push_back(9);
	upRightAnimation.push_back(11);

	currentAnimation = rightAnimation;
	itAnimation = currentAnimation.begin();
	currentStates[States::Right] = true;
}

Character::~Character()
{
	printf("Delete Character\n");
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

	if (currentInput[Input::Up] && currentStates[States::Right]) {
		currentStates[States::UpRight] = true;
	}
	else {
		currentStates[States::UpRight] = false;
	}

	if (currentInput[Input::Up] && currentStates[States::Left]) {
		currentStates[States::UpLeft] = true;
	}
	else {
		currentStates[States::UpLeft] = false;
	}

	if (currentStates[States::CanRight] && currentInput[Input::Right]) {
		if (abs(velocity.x) < velocityMax.x) {
			velocity.x += 50;
		}
		currentStates[States::Right] = true;
		currentStates[States::Left] = false;
	}
	else if (currentStates[States::CanLeft] && currentInput[Input::Left]) {
		if (abs(velocity.x) < velocityMax.x) {
			velocity.x -= 50;
		}
		currentStates[States::Right] = false;
		currentStates[States::Left] = true;
	}
	else if(currentStates[States::OnFloor]){
		if (velocity.x > 10 && currentStates[States::CanRight]) {
			velocity.x -= 25;
		}
		else if (velocity.x < -10 && currentStates[States::CanLeft]) {
			velocity.x += 25;
		}
		else {
			velocity.x = 0;
		}
	}
	else {
		if (velocity.x > 10 && currentStates[States::CanRight]) {
			velocity.x -= 8;
		}
		else if (velocity.x < -10 && currentStates[States::CanLeft]) {
			velocity.x += 8;
		}
		else {
			velocity.x = 0;
		}

	}

	if ((currentStates[States::CanJumpe] && currentInput[Input::Jumpe] 
		&& !currentStates[States::CanFall] && currentStates[States::OnFloor]) 
		|| (tempe_AccelY && currentInput[Input::Jumpe])) {
		if (abs(velocity.y) < velocityMax.y)
		{
			velocity.y -= 50;
			currentStates[States::OnFloor] = false;
			tempe_AccelY = true;
		}
		else {
			tempe_AccelY = false;
		}
	}
	
	int i = 0;
	for (auto& bullet : bulletList) {
		bullet->Update(deltaTime);
		if (!bullet->life) {
			++i;
		}
	}

	for (; i > 0; --i) {
		bulletList.pop_front();
	}

	if (currentStates[States::UpRight]) {
		currentAnimation = upRightAnimation;
	}
	else if (currentStates[States::UpLeft]) {
		currentAnimation = upLeftAnimation;
	}
	else if (currentStates[States::Right]) {
		currentAnimation = rightAnimation;
	}
	else if (currentStates[States::Left]) {
		currentAnimation = leftAnimation;
	}

	if (animationTimer >= 0.1f && velocity.x !=0 && !currentStates[States::CanFall]) {
		animationTimer = 0.f;
		++itAnimation;
	}

	if (itAnimation == currentAnimation.end()) {
		itAnimation = currentAnimation.begin();
	}

	position.x += velocity.x*deltaTime;
	position.y += velocity.y*deltaTime;

	animationTimer += deltaTime;
	bulletTimer += deltaTime;
	useClip = *itAnimation;


	currentStates[States::CanFall] = true;
	currentStates[States::CanJumpe] = true;
	currentStates[States::CanRight] = true;
	currentStates[States::CanLeft] = true;
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
				currentStates[States::OnFloor] = true;
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
				bulletList.push_back(std::make_shared<Bullet>(position, currentStates[States::Right], "Bullet.png", ren));
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
	}

	if (((position.x - collisionBoxX.x) - 4.f) < ((obj->position.x + obj->collisionBox.x) + 4.f) &&
		((position.x - collisionBoxX.x) + 4.f) > ((obj->position.x + obj->collisionBox.x) - 4.f) &&
		(position.y - collisionBoxX.y) < (obj->position.y + obj->collisionBox.y) &&
		(position.y + collisionBoxX.y) > (obj->position.y - obj->collisionBox.y)) {
		currentStates[States::CanLeft] = false;
	}

	if (((position.x + collisionBoxX.x) - 4.f) < ((obj->position.x - obj->collisionBox.x) + 4.f) &&
		((position.x + collisionBoxX.x) + 4.f) > ((obj->position.x - obj->collisionBox.x) - 4.f) &&
		(position.y - collisionBoxX.y) < (obj->position.y + obj->collisionBox.y) &&
		(position.y + collisionBoxX.y) > (obj->position.y - obj->collisionBox.y)) {
		currentStates[States::CanRight] = false;
	}

}
