#pragma once

#include "Object.h"

class SphereGlm : public Object {
public:
	SphereGlm(const glm::vec3& pos, float size);
	SphereGlm(const Transform& _transform);
	virtual ~SphereGlm() {}

	glm::vec3 pos;
	float radius;

	virtual Intersection Intersect(const Ray& ray, float min, float max) override;
};