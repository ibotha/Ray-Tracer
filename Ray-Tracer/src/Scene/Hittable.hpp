#pragma once
#include <Ray.h>
#include <HitRecord.h>

class Hittable
{
public:
	virtual bool Intersect(const Ray& r, HitRecord& rec, float min, float max) const = 0;
};

