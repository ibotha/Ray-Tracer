#include "Plane.h"
#include <iostream>

Plane::Plane(const glm::vec3& _point, const glm::vec3& _normal)
	:Object(
		Transform(_point, glm::vec3(0), glm::vec3(0))
	){
	auto _normal_normed = glm::normalize(_normal);

	point = _point;
	normal = _normal_normed;
	/* ax + by + cz - (a*x0 + b*y0 + c*z0) = 0 */
	double offset = -1 * (
		(double)_normal_normed[0] * (double)_point[0] + 
		(double)_normal_normed[1] * (double)_point[1] + 
		(double)_normal_normed[2] * (double)_point[2]);
	/* The offset is the distance from the origin to plane*/
	coefs = { _normal_normed[0], _normal_normed[1], _normal_normed[2], offset};
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

	float numer = -1 * (coefs[0] * rP[0] + coefs[1] * rP[1] + coefs[2] * rP[2]);

	// dist is the multiple of the ray unit vector to hit the plane.
	float dist = numer / overlap; // this shouldn't be zero since a parallel ray possibility has been eliminated.
	// if dist is in range we have a hit, otherwise the hit is behind the ray cast.
	if (dist < min || dist > max) {
		i.hit = false;
		return i;
	}

	i.hit = true;
	i.dist = dist;
	i.location = ray.origin + ray.direction * dist;
	i.outer_face = overlap < 0;
	i.normal = i.outer_face ? normal : -normal;
	return i;
}