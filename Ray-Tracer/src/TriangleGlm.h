#pragma once

#include "Plane.h"

class TriangleGlm : public Plane {
public:
	TriangleGlm(const glm::vec3& pointA, const glm::vec3& pointB, const glm::vec3& pointC);
	virtual ~TriangleGlm() {}
	virtual Intersection Intersect(const Ray& ray, float min, float max) override;

protected:
	glm::vec3 pointA;
	glm::vec3 pointB;
	glm::vec3 pointC;
};