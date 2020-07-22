#pragma once
#include <glm/glm.hpp>
class Object;

struct Intersection
{
	Object *object = nullptr;
	float dist = INFINITY;
	glm::vec3 location = glm::vec3(0, 0, 0);
	glm::vec3 normal = glm::vec3(0, 1, 0);
	bool hit = false;
};