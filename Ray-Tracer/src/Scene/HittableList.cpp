#include "HittableList.hpp"
#include <print_helpers.h>


HittableList::HittableList()
{
}

bool HittableList::Intersect(const Ray& r, HitRecord& rec, float t_min, float t_max) const
{
	if (!m_AABB.hit(r, t_min, t_max))
		return false;

	rec.t = INFINITY;
	for (auto& h : children) {
		HitRecord local_rec;
		if (h->Intersect(r, local_rec, t_min, t_max) && local_rec.t < rec.t)
			rec = local_rec;
	}
	if (rec.t != INFINITY)
		return true;
	return false;
}

bool HittableList::GetBounds(AABB&out) const
{
	out = m_AABB;
	return true;
}

void HittableList::RecalculateBounds()
{
	m_AABB.min = glm::vec3(INFINITY);
	m_AABB.max = glm::vec3(-INFINITY);
	for (auto& a : children) {
		AABB aabb;
		a->GetBounds(aabb);
		m_AABB.min = glm::min(m_AABB.min, aabb.min);
		m_AABB.max = glm::max(m_AABB.max, aabb.max);
	}
}
