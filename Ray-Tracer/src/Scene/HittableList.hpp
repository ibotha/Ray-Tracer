#pragma once
#include <vector>
#include <Ray.h>
#include <HitRecord.h>
#include <Scene/AABB.hpp>
#include <Scene/Hittable.hpp>

class HittableList : public Hittable
{
public:
	HittableList();

	virtual bool Intersect(const Ray& r, HitRecord& rec, float min, float max) const;
	bool GetBounds(AABB& out) const;
	void RecalculateBounds();

	std::vector<std::shared_ptr<Hittable>> children;

private:
	AABB m_AABB;
};

