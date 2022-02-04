#include "Camera.h"
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <conversion.h>
#include <print_helpers.h>
#include <Ray.h>

Camera::Camera(const aiCamera* camera, aiNode* node)
{
	view = (aiGetNodeWorldMatrix(node));
	FOV = camera->mHorizontalFOV;
	AR = camera->mAspect;
	position = glm::vec3(glm::vec4(aiVec3DToGLMVec3(camera->mPosition), 1.0f) * view);
	glm::vec3 lookAt = glm::normalize(aiVec3DToGLMVec3(camera->mLookAt) * glm::mat3(view));
	glm::vec3 up = glm::normalize(aiVec3DToGLMVec3(camera->mUp) * glm::mat3(view));
	glm::vec3 right = glm::cross(lookAt, up);
	std::cout << view << std::endl << position << lookAt << up << right << std::endl;
	float half_width = glm::tan(FOV / 2.0f);
	float half_height = half_width / AR;
	lower_left_corner = lookAt - half_height * up - half_width * right;;
	horizontal = right * 2.f * half_width;
	vertical = up * 2.f * half_height;
	name = camera->mName.C_Str();
}



Ray Camera::GenerateRay(float x, float y) const
{
	Ray ray{
		position,
		glm::normalize(lower_left_corner + x * horizontal + y * vertical)
	};
	return ray;
}
