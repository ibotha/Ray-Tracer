#include "Sphere.h"
#include <iostream>

Sphere::Sphere(const glm::vec3& pos, float size)
	:Object(Transform(pos, glm::vec3(0), glm::vec3(size)))
{
}

Sphere::Sphere(const Transform& _transform)
	:Object(_transform)
{
}

Intersection Sphere::Intersect(const Ray& ray)
{
	Intersection i;

	Ray local = transform.ToObjectSpace(ray);
	//std::cout << local.direction.x << " " << local.direction.y << " " << local.direction.z << std::endl;
	//std::cout << local.origin.x << " " << local.origin.y << " " << local.origin.z << std::endl;

	float a = glm::dot(local.direction, local.direction);
	float b = 2.0f * glm::dot(local.origin, local.direction);
	float c = glm::dot(local.origin, local.origin) - 1;
	float discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
	{
		glm::vec3 hit_location;
		i.dist = (-b - glm::sqrt(discriminant)) / (2.0f * a);
		i.hit = i.dist > 0;
		if (!i.hit)
			return i;
		hit_location = local.origin + local.direction * i.dist;
		i.location = transform.ToWorldSpace(hit_location);
		i.SetNormal(ray, glm::normalize(transform.ToWorldSpaceDir(hit_location)));
	}
	else
		i.hit = false;
	return i;
}
