#pragma once
#include <glm/glm.hpp>
#include <Ray.h>

struct HitRecord
{
	glm::vec3 point;
	glm::vec3 normal;
	int mIndex;
	float t;
	bool inside;

	inline void SetNormal(const Ray& r, glm::vec3 outside_normal) {
		if (glm::dot(r.direction, normal) > 0) {
			normal = outside_normal;
			inside = false;
		}
		else {
			normal = -outside_normal;
			inside = true;
		}
	}
};

