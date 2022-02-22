#include "Camera.h"
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <conversion.h>
#include <print_helpers.h>
#include <Ray.h>
#include <Random.h>

Camera::Camera(const aiCamera* camera, aiNode* node)
{
	float aperture = 0.0f;
	float focus_dist = 1160.0f;
	view = (aiGetNodeWorldMatrix(node));
	FOV = camera->mHorizontalFOV;
	AR = camera->mAspect;
	position = glm::vec3(glm::vec4(aiVec3DToGLMVec3(camera->mPosition), 1.0f) * view);
	w = glm::normalize(aiVec3DToGLMVec3(camera->mLookAt) * glm::mat3(view));
	v = glm::normalize(aiVec3DToGLMVec3(camera->mUp) * glm::mat3(view));
	u = glm::cross(w, v);
	std::cout << position << w << u << v << std::endl;

	float h = glm::tan(FOV / 2.0f);
	float viewport_width = h * 2.0f;
	float viewport_height = viewport_width / AR;

	horizontal = focus_dist * viewport_width * u;
	vertical = focus_dist * viewport_height * v;
	lower_left_corner = position - horizontal/2.0f - vertical/2.0f + focus_dist*w;
	std::cout <<
		"Lower left: " << lower_left_corner <<
		"Verical: " << vertical <<
		"Horizontal: " << horizontal <<
		std::endl;

	name = camera->mName.C_Str();
	lens_radius = aperture / 2;
}



Ray Camera::GenerateRay(float x, float y) const
{
	glm::vec3 rd = lens_radius * Random::InUnitDisk();
	glm::vec3 offset = u * rd.x + v * rd.y;

	Ray ray{
		position + offset,
		glm::normalize(lower_left_corner + x * horizontal + y * vertical - position - offset)
	};
	return ray;
}
