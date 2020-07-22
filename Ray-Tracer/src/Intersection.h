#pragma once
#include <glm/glm.hpp>
#include "Ray.h"
#include <memory>
class Object;

struct Intersection
{
	std::shared_ptr<Object> object;
	float dist = INFINITY;
	glm::vec3 location = glm::vec3(0, 0, 0);
	glm::vec3 normal = glm::vec3(0, 1, 0);
	bool hit = false;
	bool inner_face = false;

	void SetNormal(const Ray& ray, const glm::vec3& outward_normal);
};