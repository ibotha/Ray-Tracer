#pragma once

#include "Object.h"

class Sphere : public Object {
public:
	Sphere(const glm::vec3 &pos, float size);
	Sphere(const Transform& _transform);
	virtual ~Sphere() {}

	glm::vec3 pos;
	float radius;

	virtual Intersection Intersect(const Ray& ray, float min, float max) override;
};