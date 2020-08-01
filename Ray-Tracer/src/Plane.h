#pragma once

#include "Object.h"

class Plane : public Object {
public:
	Plane(const glm::vec3& pos);
	Plane(const glm::vec3& _point, const glm::vec3& _normal);
	void Init(const glm::vec3& _point, const glm::vec3& _normal);
	virtual ~Plane() {}
	virtual Intersection Intersect(const Ray& ray, float min, float max) override;
protected:
	/* Planes are in the form Ax + By + Cz + D = 0 */
	/* The offset is the distance from the origin to plane*/
	float offset;
	// The point through which the plane passes.
	glm::vec3 point;
	// The plane normal.
	glm::vec3 normal;
};
