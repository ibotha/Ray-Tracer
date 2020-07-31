#include "Disk.h"
#include <iostream>

Disk::Disk(const glm::vec3& _point, const glm::vec3& _normal, const float _radius)
	: Plane(_point, _normal)
{
	radius = _radius;
}

Intersection Disk::Intersect(const Ray& ray, float min, float max) {
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
	float dist = numer / overlap; // this shouldn't be zero since a parallel ray possibility has been eliminated.
	// if dist is in range we have a hit, otherwise the hit is behind the ray cast.
	if (dist < min || dist > max) {
		i.hit = false;
		return i;
	}

	i.location = ray.origin + ray.direction * dist;
	auto hitDist = glm::distance(i.location, point);

	if (hitDist < radius) {
		i.hit = true;
		i.dist = dist;
		i.outer_face = overlap < 0;
		i.normal = i.outer_face ? normal : -normal;
	}
	return i;
}