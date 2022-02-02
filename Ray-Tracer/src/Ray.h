#pragma once
#include <glm/glm.hpp>
#include <iostream>

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray Transform(const glm::mat4& mat);
};

std::ostream& operator<<(std::ostream& out, Ray r);

