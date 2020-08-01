#pragma once

#include "Plane.h"

class Triangle : public Plane {
public:
	Triangle(const glm::vec3& pointA, const glm::vec3& pointB, const glm::vec3& pointC);
	virtual ~Triangle() {}
	virtual Intersection Intersect(const Ray& ray, float min, float max) override;

	glm::vec3 AreaV(glm::vec3& A, glm::vec3& B, glm::vec3& C);
	float Magnitude(glm::vec3& A);
	float AreaTri(glm::vec3& A, glm::vec3& B, glm::vec3 C);

protected:
	glm::vec3 pointA;
	glm::vec3 pointB;
	glm::vec3 pointC;
	float area;
};
