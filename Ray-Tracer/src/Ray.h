#pragma once

#include <glm/glm.hpp>

struct Ray {
	Ray(const glm::vec3& _origin, const glm::vec3& _direction) : origin(_origin), direction(_direction) {}
	glm::vec3 origin;
	glm::vec3 direction;

	inline void Normalize() { direction = glm::normalize(direction); }

	Ray Transform(const glm::mat4& matrix) const;
};