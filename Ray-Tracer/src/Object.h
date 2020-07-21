#pragma once
#include "Ray.h"
#include "Intersection.h"
#include "Material.h"

//abstract object class
class Object
{
public:
	Object(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);
	virtual ~Object() {}

	virtual Intersection Intersect(const Ray& ray) = 0;

	Material mat;

	// matrix for holding translation, rotation, and scale of an object. Used for transforming to object space from world space;
	glm::mat4 transform;

	// Same as transform but for returning from object space to world space
	glm::mat4 invtransform;

};