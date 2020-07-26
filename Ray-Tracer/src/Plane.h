#pragma once

#include "Object.h"

class Plane : public Object {
public:
	Plane(const glm::vec3& normal, const glm::vec3& pos);
	virtual ~Plane() {}

	virtual Intersection Intersect(const Ray& ray, float min, float max) override;

protected:
	/* Planes are in the form Ax + By + Cz + D = 0 */
	glm::vec4 coefs;
	// The point through which the plane passes.
	glm::vec3 point;
	// The plane normal.
	glm::vec3 normal;
};