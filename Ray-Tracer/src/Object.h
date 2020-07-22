#pragma once
#include "Ray.h"
#include "Intersection.h"
#include "Material.h"
#include "Transform.h"

//abstract object class
class Object
{
public:
	Object(const Transform& transform);
	virtual ~Object() {}

	virtual Intersection Intersect(const Ray& ray) { return Intersection(); };

	std::shared_ptr<Material> mat;

	// matrix for holding translation, rotation, and scale of an object. Used for transforming to object space from world space;
	Transform transform;
};