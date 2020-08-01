#include "SphereGlm.h"
#include <iostream>
#include "glm/gtx/intersect.hpp"

SphereGlm::SphereGlm(const glm::vec3& _pos, float _radius)
	:Object(Transform(_pos, glm::vec3(0), glm::vec3(_radius))), pos(_pos), radius(_radius) {
	pos = _pos;
	radius = _radius;
}

SphereGlm::SphereGlm(const Transform& _transform)
	: Object(_transform) {
	pos = glm::vec3(0, 0, 0);
	radius = 0;
}

Intersection SphereGlm::Intersect(const Ray& ray, float min, float max) {
	Intersection i;

	glm::vec3 location;
	glm::vec3 normal;
	i.hit = glm::intersectRaySphere(ray.origin, ray.direction, pos, radius, location, normal);
	i.location = location;
	i.SetNormal(ray, normal);
	i.dist = glm::distance(i.location, ray.origin);
	return i;
}
