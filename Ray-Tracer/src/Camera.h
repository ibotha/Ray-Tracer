#pragma once

#include <glm/glm.hpp>
#include "Transform.h"

struct Camera
{
public:
	Camera(const glm::vec3& pos, const glm::vec3& rot);
	float FOV;

	Transform transform;
};