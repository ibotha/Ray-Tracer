#pragma once

#include <glm/glm.hpp>
#include "Ray.h"

class Sphere {
public:
	Sphere(const glm::vec3 &pos, float size);

	bool Intersect(const Ray& ray);
};