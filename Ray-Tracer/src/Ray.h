#pragma once

#include <glm/glm.hpp>

struct Ray {
	Ray(const glm::vec3& _origin = glm::vec3(0,0,0), const glm::vec3& _direction = glm::vec3(1, 0, 0)) : origin(_origin), direction(_direction) {}
	glm::vec3 origin;
	glm::vec3 direction;

	inline void Normalize() { direction = glm::normalize(direction); }

	Ray Transform(const glm::mat4& matrix) const;
};