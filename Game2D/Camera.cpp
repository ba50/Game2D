#pragma once

#include "Camera.h"
#include "Define.h"

Camera::Camera(Vecf2 position, float width, float height) :
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

void Camera::MoveTo(Vecf2 newPosition)
{
	position.x = newPosition.x - toCenter.x;
//	if ((newPosition.y-position.y) < 0) {
//		position.y = newPosition.y - toCenter.y;
//	}
//	if ((newPosition.y-position.y) > SCREEN_HEIGHT) {
//		position.y = newPosition.y - toCenter.y;
//	}
}