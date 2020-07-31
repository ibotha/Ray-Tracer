#include "Plane.h"
#include "Object.h"
#include <iostream>

Plane::Plane(const glm::vec3& _point)
	:Object(
		Transform(_point, glm::vec3(0), glm::vec3(0))
	) {
	point = _point;
}

Plane::Plane(const glm::vec3& _point, const glm::vec3& _normal)
	:Object(
		Transform(_point, glm::vec3(0), glm::vec3(0))
	) {
	Init(_point, _normal);
}

void Plane::Init(const glm::vec3& _point, const glm::vec3& _normal) {
	// If the normal is zero, weird things happen

	if (glm::dot(_normal, _normal) != 0.0)
		normal = glm::normalize(_normal); // Normalizing a zero gives weird results, so avoid it.
	else
		normal = _normal;

	point = _point;
	/* ax + by + cz - (a*x0 + b*y0 + c*z0) = 0 */
	offset = -1 * (glm::dot(normal, point));
}

Intersection Plane::Intersect(const Ray& ray, float min, float max) {
	Intersection i;

	auto rP = ray.origin;
	auto rD = ray.direction;

	double overlap = glm::dot(rD, normal);
	if (overlap == 0) {
		i.hit = false;
		return i;
	}

	float numer = -1 * (glm::dot(normal, rP) + offset);
	// dist is the multiple of the ray unit vector to hit the plane.
	float dist = numer / overlap;
	if (dist < min || dist > max) {
		i.hit = false;
		return i;
	}

	i.location = ray.origin + ray.direction * dist;
	i.hit = true;
	i.dist = dist;
	i.outer_face = overlap < 0;
	i.normal = i.outer_face ? normal : -normal;
	return i;
}