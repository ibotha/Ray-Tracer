#include "AABB.hpp"

AABB::AABB(const glm::vec3& _min, const glm::vec3& _max)
{
	min = _min;
	max = _max;
}

bool AABB::hit(const Ray& r, float t_min, float t_max) const
{
	for (int a = 0; a < 3; a++) {
		auto invD = 1.0f / r.direction[a];
		auto t0 = (min[a] - r.origin[a]) * invD;
		auto t1 = (max[a] - r.origin[a]) * invD;
		if (invD < 0.0f)
			std::swap(t0, t1);
		t_min = t0 > t_min ? t0 : t_min;
		t_max = t1 < t_max ? t1 : t_max;
		if (t_max <= t_min)
			return false;
	}
	return true;
}

AABB AABB::SurroundingBox(const AABB& a, const AABB& b)
{
	glm::vec3 small = glm::min(a.min, b.min);
	glm::vec3 big = glm::max(a.max, b.max);
	return AABB(small, big);
}
