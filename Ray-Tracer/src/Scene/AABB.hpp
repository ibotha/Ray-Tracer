#pragma once
#include <glm/glm.hpp>
#include <Ray.h>


class AABB {
public:
	AABB(const glm::vec3& min = glm::vec3(0), const glm::vec3& max = glm::vec3(0));
	glm::vec3 min;
	glm::vec3 max;

	bool hit(const Ray& r, float t_min, float t_max) const;

	static AABB SurroundingBox(const AABB& a, const AABB& b);
};