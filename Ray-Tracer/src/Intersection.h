#pragma once
#include <glm/glm.hpp>
class Object;

struct Intersection
{
	Object *object = nullptr;
	float dist;
	glm::vec3 location;
	glm::vec3 normal;
	bool hit;
};