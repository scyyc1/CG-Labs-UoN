#pragma once

#include <glm/glm/glm.hpp>
#include "camera.h"

#define DEG2RAD(n)	n*(3.14/180)

void MoveCamera(SCamera& in, SCamera::Camera_Movement direction)
{
	bool change = false;
	switch (direction) {
	case SCamera::FORWARD: {
		in.Position += in.Front * in.MovementSpeed;
		change = true;
		break;
	}
	case SCamera::BACKWARD: {
		in.Position -= in.Front * in.MovementSpeed;
		change = true;
		break;
	}
	case SCamera::LEFT: {
		in.Position += in.Right * in.MovementSpeed;
		change = true;
		break;
	}
	case SCamera::RIGHT: {
		in.Position -= in.Right * in.MovementSpeed;
		change = true;
		break;
	}
	}
	//if (change)
	//	std::cout << in.Position.x << " "
	//	<< in.Position.y << " "
	//	<< in.Position.z << " "
	//	<< std::endl;
}

void OrientCamera(SCamera& in, float xoffset, float yoffset)
{
	in.Yaw -= xoffset * in.MouseSensitivity;
	in.Pitch += yoffset * in.MouseSensitivity;

	if (in.Pitch > 89.f)	in.Pitch = 89.f;
	if (in.Pitch < -89.f)	in.Pitch = -89.f;

	float p_x = cos(DEG2RAD(in.Yaw)) * cos(DEG2RAD(in.Pitch));
	float p_y = sin(DEG2RAD(in.Pitch));
	float p_z = sin(DEG2RAD(in.Yaw)) * cos(DEG2RAD(in.Pitch));
	glm::vec3 new_pos = glm::vec3(p_x, p_y, p_z);

	in.Front = glm::normalize(new_pos - in.Position);
	in.Right = glm::normalize(glm::cross(in.Front, in.WorldUp));
	in.Up = glm::normalize(glm::cross(in.Front, in.Right));
}