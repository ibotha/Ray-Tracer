#pragma once

#include "Object.h"

class Sphere : public Object {
public:
	Sphere(const glm::vec3 &pos, float size);

	Intersection Intersect(const Ray& ray) override;
};