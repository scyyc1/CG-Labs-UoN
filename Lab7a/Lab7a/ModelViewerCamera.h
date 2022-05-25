#pragma once

#include <stdio.h>
#include <glm/glm/glm.hpp>
#include "camera.h"
#include "math.h"

float cam_dist = 2.f;

#define DEG2RAD(n)	n*(3.14/180)

void MoveAndOrientCamera(SCamera& in, glm::vec3 target, float distance, float xoffset, float yoffset)
{
	in.Yaw -= xoffset * in.MovementSpeed;
	in.Pitch -= yoffset * in.MovementSpeed;

	if (in.Pitch > 89.f)	in.Pitch = 89.f;
	if (in.Pitch < -89.f)	in.Pitch = -89.f;

	in.Position.x = cos(DEG2RAD(in.Yaw)) * cos(DEG2RAD(in.Pitch));
	in.Position.y = sin(DEG2RAD(in.Pitch));
	in.Position.z = sin(DEG2RAD(in.Yaw)) * cos(DEG2RAD(in.Pitch));

	in.Front = glm::normalize(target - in.Position);
	in.Right = glm::normalize(glm::cross(in.Front, in.WorldUp));
	in.Up = glm::normalize(glm::cross(in.Front, in.Right));

	in.Position *= distance;
}