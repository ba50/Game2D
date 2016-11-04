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
	position.x = cha->position.x - toCenter.x;
	position.y = cha->position.y - toCenter.y;
}