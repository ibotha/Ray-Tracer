#pragma once

#include "Object.h"

class Sphere : public Object {
public:
	Sphere(const glm::vec3 &pos, float size);
	Sphere(const Transform& _transform);
	virtual ~Sphere() {}

	virtual Intersection Intersect(const Ray& ray) override;
};