#pragma once
#include <glm/glm.hpp>
#include <iostream>

struct Ray
{
	Ray(glm::vec3 _origin, glm::vec3 _direction);
	Ray():origin(0.0f), direction(0.0f) {}
	glm::vec3 origin;
	glm::vec3 direction;

	Ray Transform(const glm::mat4& mat) const;
	inline glm::vec3 At(float dist) const {
		return origin + direction * dist;
	}
};

std::ostream& operator<<(std::ostream& out, Ray r);

