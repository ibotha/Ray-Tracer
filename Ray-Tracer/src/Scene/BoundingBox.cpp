#include "BoundingBox.hpp"

BoundingBox::BoundingBox(const std::vector<std::shared_ptr<Hittable>>& hittables)
{
	x0 = 100;
	x1 = -100;
	y0 = 100;
	y1 = -100;
	z0 = 100;
	z1 = -100;

	for (auto& a : hittables)
		m_Children.push_back(a);
}

bool BoundingBox::Intersect(const Ray& r, HitRecord& rec, float min, float max) const
{
	bool ray_intersects_bounds = true;

	if (ray_intersects_bounds) {
		rec.t = INFINITY;
		for (auto& h : m_Children) {
			HitRecord local_rec;
			if (h->Intersect(r, local_rec, min, max) && local_rec.t < rec.t)
				rec = local_rec;
		}
		if (rec.t != INFINITY)
			return true;
	}
	return false;
}
