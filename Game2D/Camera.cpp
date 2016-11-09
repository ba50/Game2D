#pragma once

#include "Camera.h"
#include "Define.h"
#include "Character.h"

Camera::Camera(Vecf2 position, float width, float height) :
	position(position),
	toCenter({ width / 2.f, height / 2.f })
{
	Camera::position.y = (position.y - toCenter.y) + BLOCK_SIZE;
}

Camera::~Camera() 
{}

Camera::Camera(const Camera &cam)
{
	position = cam.position;
	toCenter = cam.toCenter;
}

void Camera::MoveTo(std::shared_ptr<Character> cha, float deltaTime)
{

	if (shake_vector.size() == 0) {
		position.x = cha->position.x - (toCenter.x - 100.f*cha->velocity.x / cha->max_velocity);
		position.y = cha->position.y - (toCenter.y - 100.f*cha->velocity.y / cha->max_velocity);
	}
	else {
		position.x = (cha->position.x - (toCenter.x - 100.f*cha->velocity.x / cha->max_velocity)) + shake_vector.back().x;
		position.y = (cha->position.y - (toCenter.y - 100.f*cha->velocity.y / cha->max_velocity)) + shake_vector.back().y;
		shake_vector.pop_back();
	}
}

void Camera::Shake(){
	if (shake_vector.size() == 0) {
		for (int i = 0; i < 5; i++) {
			shake_vector.push_back(Vecf2{
				.005f*SCREEN_WIDTH*sinf(Math::Rand(0,2 * PI)),
				.005f*SCREEN_HEIGHT*cosf(Math::Rand(0,2 * PI)),
			});
		}
	}
}