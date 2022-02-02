#pragma once
#include <glm/glm.hpp>

struct HitRecord
{
	glm::vec3 point;
	glm::vec3 normal;
	glm::vec3 colour;
	float t;
};

