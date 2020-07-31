#include "TriangleGlm.h"
#include "glm/gtx/normal.hpp"
#include "glm/gtx/intersect.hpp"

TriangleGlm::TriangleGlm(const glm::vec3& _pointA, const glm::vec3& _pointB, const glm::vec3& _pointC)
    : Plane((pointA + pointB + pointC) / 3.0f)
{
    pointA = _pointA;
    pointB = _pointB;
    pointC = _pointC;
    normal = glm::triangleNormal(pointA, pointB, pointC);
    Init(point, normal);
}

Intersection TriangleGlm::Intersect(const Ray& ray, float min, float max) {
    auto i = Plane::Intersect(ray, min, max);
    glm::vec2 position;
    float distance;
    i.hit = glm::intersectRayTriangle(ray.origin, ray.direction, pointA, pointB, pointC, position, distance);
    return i;
}
