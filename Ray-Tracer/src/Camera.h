#pragma once

#include <glm/glm.hpp>
#include <stdio.h>
#include "Transform.h"

struct Camera
{
public:
	Camera(const glm::vec3& pos, const glm::vec3& rot, float _FOV = 60.0f);
	float FOV;

	Transform transform;
};