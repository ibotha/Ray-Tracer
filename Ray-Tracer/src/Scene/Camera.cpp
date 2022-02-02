#include "Camera.h"
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <conversion.h>
#include <print_helpers.h>

Camera::Camera(const aiCamera* camera, aiNode* node)
{
	glm::mat4 transform = (aiGetNodeWorldMatrix(node));
	m_FOV = camera->mHorizontalFOV;
	m_AR = camera->mAspect;
	m_Position = glm::vec3(glm::vec4(aiVec3DToGLMVec3(camera->mPosition), 1.0f) * transform);
	glm::vec3 lookAt = aiVec3DToGLMVec3(camera->mLookAt) * glm::mat3(transform);
	glm::vec3 up = aiVec3DToGLMVec3(camera->mUp) * glm::mat3(transform);
	m_View = transform;
	float half_width = glm::tan(m_FOV / 2.0f);
	float half_height = half_width / m_AR;
	lower_left_corner = glm::vec3(1, -half_height, -half_width);
	horizontal = glm::vec3(0, 0, 2 * half_width);
	vertical = glm::vec3(0, 2 * half_height, 0.0);
}
