#pragma once

#include <glm/glm.hpp>

struct Camera
{
public:
	Camera(const glm::vec3& pos, const glm::vec3& rot);
	float FOV;

	// matrix for holding translation, rotation of the camera. Used for transforming to camera space from world space;
	glm::mat4 transform;

	// Same as transform but for returning from camera space to world space
	glm::mat4 invtransform;
};