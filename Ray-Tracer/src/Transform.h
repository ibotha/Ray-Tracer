#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Ray.h"

class Transform
{
public:
	Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);
	Transform(const glm::mat4& base);
	Ray ToObjectSpace(const Ray& ray) const;
	Ray ToWorldSpace(const Ray& ray) const;

	glm::vec3 ToObjectSpaceDir(const glm::vec3& dir) const;
	glm::vec3 ToWorldSpaceDir(const glm::vec3& dir) const;

	glm::vec3 ToObjectSpace(const glm::vec3& vec) const;
	glm::vec3 ToWorldSpace(const glm::vec3& vec) const;

private:
	glm::mat4 otw;
	glm::mat4 wto;
	glm::mat3 otwDir;
	glm::mat3 wtoDir;
};