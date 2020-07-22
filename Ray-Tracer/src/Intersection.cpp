#include "Intersection.h"

void Intersection::SetNormal(const Ray& ray, const glm::vec3& outward_normal)
{
	inner_face = !glm::dot(ray.direction, outward_normal) < 0;
	normal = inner_face ? -outward_normal : outward_normal;
}
