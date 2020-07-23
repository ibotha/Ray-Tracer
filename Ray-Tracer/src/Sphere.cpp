#include "Sphere.h"
#include <iostream>

Sphere::Sphere(const glm::vec3& _pos, float size)
	:Object(Transform(_pos, glm::vec3(0), glm::vec3(size))), pos(_pos), radius(size)
{
}

Sphere::Sphere(const Transform& _transform)
	:Object(_transform)
{
}

Intersection Sphere::Intersect(const Ray& ray, float min, float max)
{
	Intersection i;
	glm::vec3 oc = ray.origin - pos;
	auto a = glm::dot(ray.direction, ray.direction);
	auto half_b = glm::dot(oc, ray.direction);
	auto c = glm::dot(oc, oc) - radius * radius;
	auto discriminant = half_b * half_b - a * c;

	if (discriminant > 0) {
		auto root = sqrt(discriminant);
		auto temp = (-half_b - root) / a;
		if (temp < max && temp > min) {
			i.dist = temp;
			i.location = ray.origin + ray.direction * i.dist;
			glm::vec3 outward_normal = (i.location - pos) / radius;
			i.SetNormal(ray, outward_normal);
			i.hit = true;
			return i;
		}
		temp = (-half_b + root) / a;
		if (temp < max && temp > min) {
			i.dist = temp;
			i.location = ray.origin + ray.direction * i.dist;
			glm::vec3 outward_normal = (i.location - pos) / radius;
			i.SetNormal(ray, outward_normal);
			i.hit = true;
			return i;
		}
	}
	return i;

	//float a = glm::dot(local.direction, local.direction);
	//float half_b = glm::dot(local.origin, local.direction);
	//float c = glm::dot(local.origin, local.origin) - 1;
	//float discriminant = half_b * half_b - a * c;
	//if (discriminant > 0)
	//{
	//	glm::vec3 hit_location;
	//	float root = glm::sqrt(discriminant);
	//	float temp = (-half_b - root) / a;
	//	if (temp < max && temp > min) {
	//		i.hit = true;
	//		i.dist = temp;
	//		hit_location = local.origin + local.direction * i.dist;
	//		i.location = transform.ToWorldSpace(hit_location);
	//		i.SetNormal(ray, glm::normalize(transform.ToWorldSpaceDir(hit_location)));
	//		return i;
	//	}

	//	temp = (-half_b + root) / a;
	//	if (temp < max && temp > min) {
	//		i.hit = true;
	//		i.dist = temp;
	//		hit_location = local.origin + local.direction * i.dist;
	//		i.location = transform.ToWorldSpace(hit_location);
	//		i.SetNormal(ray, glm::normalize(transform.ToWorldSpaceDir(hit_location)));
	//		return i;
	//	}
	//	return i;
	//}
	//else
	//	i.hit = false;
	//return i;
}
