#include "Character.h"

#include "Inputs.h"
#include "Define.h"
#include "Texture.h"

#include "Bullet.h"

std::vector<bool> Inputs::slope;

Character::Character(const float x, const float y, const std::string &file, std::shared_ptr<Renderer> & ren) :
	Object(ren),
	life(true)
{
	width = BLOCK_SIZE;
	height = BLOCK_SIZE;
	position.x = x;
	position.y = y;
	velocityMax = Vecf2{ 400.f,400.f };
	sprite = std::make_shared<Texture>(file, Object::ren);

	for (int i = 0; i < 11; ++i) {
		for (int j = 0; j < 2; ++j) {

			clips.push_back(SDL_Rect{ i * static_cast<int>(width), j * static_cast<int>(height), static_cast<int>(width), static_cast<int>(height) });

		}
	}

	Inputs::slope.push_back(false);
	Inputs::slope.push_back(false);

	collisionBoxX.x = (width - 18) / 2;
	collisionBoxX.y = (height - 25) / 2;

	collisionBoxY.x = (width - 25) / 2;
	collisionBoxY.y = (height - 20) / 2;

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
	currentStates[States::OnFloor] = true;

}

Character::~Character()
{
	printf("Delete Character\n");
}

void Character::Update(const float deltaTime)
{
	velocity.y += 100.f;

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

	if (currentInput[Input::Right]) {
		if (velocity.x < 0) {
			velocity.x = 0;
		}

		if (abs(velocity.x) < velocityMax.x) {
			velocity.x += 50;
		}
		currentStates[States::Right] = true;
		currentStates[States::Left] = false;
	}
	else if (currentInput[Input::Left]) {
		if (velocity.x > 0) {
			velocity.x = 0;
		}

		if (abs(velocity.x) < velocityMax.x) {
			velocity.x -= 50;
		}
		currentStates[States::Right] = false;
		currentStates[States::Left] = true;
	}
	else if (!currentStates[States::CanFall]) {
		if (velocity.x > 10 && currentStates[States::CanRight]) {
			velocity.x -= 25;
		}
		else if (velocity.x < -10) {
			velocity.x += 25;
		}
		else {
			velocity.x = 0;
		}
	}
	else {
		if (velocity.x > 10){
			velocity.x -= 8;
		}
		else if (velocity.x < -10 && currentStates[States::CanLeft]) {
			velocity.x += 8;
		}
		else {
			velocity.x = 0;
		}
	}

	if (currentStates[States::CanJumpe] && currentInput[Input::Jumpe] && !currentStates[States::CanFall] && currentStates[States::OnFloor]){
		if (abs(velocity.y) < velocityMax.y)
		{
			velocity.y = -1500.f;
			currentStates[States::OnFloor] = false;
			currentStates[States::InAir] = true;
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

	if (animationTimer >= 0.1f && velocity.x != 0 && !currentStates[States::CanFall]) {
		animationTimer = 0.f;
		++itAnimation;
	}

	if (itAnimation == currentAnimation.end()) {
		itAnimation = currentAnimation.begin();
	}

	newPosition.x = position.x + velocity.x*deltaTime;
	newPosition.y = position.y + velocity.y*deltaTime;

	for (auto& obj : collisionList) {
		if ((newPosition.x - collisionBoxY.x) < (obj->position.x + obj->collisionBox.x) &&
			(newPosition.x + collisionBoxY.x) > (obj->position.x - obj->collisionBox.x) &&
			((newPosition.y - collisionBoxY.y) - 10.f) < ((obj->position.y + obj->collisionBox.y) + 4.f) &&
			((newPosition.y - collisionBoxY.y) + 4.f) > ((obj->position.y + obj->collisionBox.y) - 10.f)) {
//			currentStates[States::CanJumpe] = false;
		}

		if ((newPosition.x - collisionBoxY.x) < (obj->position.x + obj->collisionBox.x) &&
			(newPosition.x + collisionBoxY.x) > (obj->position.x - obj->collisionBox.x) &&
			((newPosition.y + collisionBoxY.y) - 10.f) < ((obj->position.y - obj->collisionBox.y) + 4.f) &&
			((newPosition.y + collisionBoxY.y) + 4.f) > ((obj->position.y - obj->collisionBox.y) - 10.f)) {
//			currentStates[States::CanFall] = false;
//			currentStates[States::InAir] = false;
		}

		if (((newPosition.x - collisionBoxX.x) - 4.f) < ((obj->position.x + obj->collisionBox.x) + 6.f) &&
			((newPosition.x - collisionBoxX.x) + 4.f) > ((obj->position.x + obj->collisionBox.x) - 4.f) &&
			(newPosition.y - collisionBoxX.y) < (obj->position.y + obj->collisionBox.y) &&
			(newPosition.y + collisionBoxX.y) > (obj->position.y - obj->collisionBox.y)) {
//			currentStates[States::CanLeft] = false;
		}

		if (((newPosition.x + collisionBoxX.x) - 4.f) < ((obj->position.x - obj->collisionBox.x) + 4.f) &&
			((newPosition.x + collisionBoxX.x) + 4.f) > ((obj->position.x - obj->collisionBox.x) - 5.f) &&
			(newPosition.y - collisionBoxX.y) < (obj->position.y + obj->collisionBox.y) &&
			(newPosition.y + collisionBoxX.y) > (obj->position.y - obj->collisionBox.y)) {
//			currentStates[States::CanRight] = false;
		}
	}
		position.x = newPosition.x;
		position.y = newPosition.y;

	animationTimer += deltaTime;
	bulletTimer += deltaTime;
	useClip = *itAnimation;

	currentStates[States::CanFall] = true;
	currentStates[States::CanJumpe] = true;
	currentStates[States::CanRight] = true;
	currentStates[States::CanLeft] = true;
}

void Character::Draw()
{
	ren->render(this);
	for (auto& bullet : bulletList) {
		bullet->Draw();
	}
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
	if (obj->collidable)
	{
		collisionList.push_front(obj);
		if ((position.x - collisionBoxY.x) < (obj->position.x + obj->collisionBox.x) &&
			(position.x + collisionBoxY.x) > (obj->position.x - obj->collisionBox.x) &&
			((position.y - collisionBoxY.y) - 10.f) < ((obj->position.y + obj->collisionBox.y) + 4.f) &&
			((position.y - collisionBoxY.y) + 4.f) > ((obj->position.y + obj->collisionBox.y) - 10.f)) {
			currentStates[States::CanJumpe] = false;
		}

		if ((position.x - collisionBoxY.x) < (obj->position.x + obj->collisionBox.x) &&
			(position.x + collisionBoxY.x) > (obj->position.x - obj->collisionBox.x) &&
			((position.y + collisionBoxY.y) - 10.f) < ((obj->position.y - obj->collisionBox.y) + 4.f) &&
			((position.y + collisionBoxY.y) + 4.f) > ((obj->position.y - obj->collisionBox.y) - 10.f)) {
			currentStates[States::CanFall] = false;
			currentStates[States::InAir]=false;
		}

		if (((position.x - collisionBoxX.x) - 4.f) < ((obj->position.x + obj->collisionBox.x) + 6.f) &&
			((position.x - collisionBoxX.x) + 4.f) > ((obj->position.x + obj->collisionBox.x) - 4.f) &&
			(position.y - collisionBoxX.y) < (obj->position.y + obj->collisionBox.y) &&
			(position.y + collisionBoxX.y) > (obj->position.y - obj->collisionBox.y)) {
			currentStates[States::CanLeft] = false;
		}

		if (((position.x + collisionBoxX.x) - 4.f) < ((obj->position.x - obj->collisionBox.x) + 4.f) &&
			((position.x + collisionBoxX.x) + 4.f) > ((obj->position.x - obj->collisionBox.x) - 5.f) &&
			(position.y - collisionBoxX.y) < (obj->position.y + obj->collisionBox.y) &&
			(position.y + collisionBoxX.y) > (obj->position.y - obj->collisionBox.y)) {
			currentStates[States::CanRight] = false;
		}
	}
}
