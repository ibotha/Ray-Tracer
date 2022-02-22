#pragma once
#include <Ray.h>
#include <HitRecord.h>
#include <Scene/AABB.hpp>

class Hittable
{
public:
	virtual bool Intersect(const Ray& r, HitRecord& rec, float min, float max) const = 0;
	virtual bool GetBounds(AABB & out) const = 0;
};

