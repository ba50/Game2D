#pragma once

#include "Camera.h"
#include "Define.h"

Camera::Camera(float width, float height) :
	position({ width,height }),
	toCenter({ width / 2.f, height / 2.f })
{

}

Camera::~Camera() 
{

}

Camera::Camera(const Camera &cam)
{
	position = cam.position;
	toCenter = cam.toCenter;
}

void Camera::MoveTo(Vecf2 newPosition)
{
	position = newPosition - toCenter;
}