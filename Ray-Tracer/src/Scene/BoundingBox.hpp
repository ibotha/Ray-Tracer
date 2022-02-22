#pragma once
#include <vector>
#include <Scene/Hittable.hpp>

class BoundingBox : public Hittable
{
public:
	BoundingBox(const std::vector<std::shared_ptr<Hittable>>& hittables);


	virtual bool Intersect(const Ray& r, HitRecord& rec, float min, float max) const;

private:
	float x0, x1, y0, y1, z0, z1;
	std::vector<std::shared_ptr<Hittable>> m_Children;
};

