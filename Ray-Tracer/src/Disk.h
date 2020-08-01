#pragma once

#include "Plane.h"

class Disk : public Plane {
public:
	Disk(const glm::vec3& pos, const glm::vec3& normal, const float diameter);
	virtual ~Disk() {}
	virtual Intersection Intersect(const Ray& ray, float min, float max) override;

protected:
	float radius;
};