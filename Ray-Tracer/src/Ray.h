#pragma once

#include <glm/glm.hpp>

struct Ray {
	glm::vec3 origin;
	glm::vec3 direction;

	inline void Normalize() { direction = glm::normalize(direction); }

	Ray Transform(const glm::mat4& matrix) const;
};