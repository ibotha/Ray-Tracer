#include "Camera.h"
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <conversion.h>
#include <print_helpers.h>

Camera::Camera(const aiCamera* camera, aiNode* node)
{
	glm::mat4 transform = glm::inverse(aiGetNodeWorldMatrix(node));
	m_FOV = camera->mHorizontalFOV;
	m_AR = camera->mAspect;
	m_Position = glm::vec3(glm::vec4(aiVec3DToGLMVec3(camera->mPosition), 1.0f) * transform);
	m_View = transform;
	float half_height = glm::tan(m_FOV / 2.0f);
	float half_width = m_AR * half_height;
	lower_left_cornder = glm::vec3(-half_width, -half_height, -1.0);
	horizontal = glm::vec3(2 * half_width, 0, 0);
	vertical = glm::vec3(0, 2 * half_height, 0.0);

	std::cout << m_Position << std::endl;
}
