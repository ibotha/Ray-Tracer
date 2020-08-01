#include "Triangle.h"

const glm::vec3 zero3 = glm::vec3(0, 0, 0);

Triangle::Triangle(const glm::vec3& _pointA, const glm::vec3& _pointB, const glm::vec3& _pointC)
    : Plane((pointA + pointB + pointC) / 3.0f, glm::vec3(0, 0, 0))
{
    pointA = _pointA;
    pointB = _pointB;
    pointC = _pointC;

    auto aV = AreaV(pointA, pointB, pointC);
    if (glm::dot(aV, aV) != 0)
        // Avoid normalizing a zero vector;
        normal = -1.0f * glm::normalize(aV);
    else
        normal = glm::vec3(0, 0, 0);

    area = Magnitude(aV) / 2.0f;
}

Intersection Triangle::Intersect(const Ray& ray, float min, float max) {
    auto i = Plane::Intersect(ray, min, max);
    if (i.hit == false)
        return i;

    // We are inside the triangle when the areas of inner partitions sum to the total area
    auto area1 = AreaTri(i.location, pointA, pointB);
    auto area2 = AreaTri(i.location, pointA, pointC);
    auto area3 = AreaTri(i.location, pointB, pointC);
    
    auto sumArea = area1 + area2 + area3;
    // The area of the internals is larger when outside the triangle
    if (sumArea - 0.1f > area)
        i.hit = false;
    else
        i.hit = true;

    return i;
}

glm::vec3 Triangle::AreaV(glm::vec3& A, glm::vec3& B, glm::vec3& C) {
    auto AtoB = B - A;
    auto AtoC = C - A;
    return glm::cross(AtoB, AtoC);
}

float Triangle::Magnitude(glm::vec3& A) {
    return glm::distance(A, zero3);
}

float Triangle::AreaTri(glm::vec3& A, glm::vec3& B, glm::vec3 C) {
    auto aV = AreaV(A, B, C);
    return Magnitude(aV) / 2.0f;
}
