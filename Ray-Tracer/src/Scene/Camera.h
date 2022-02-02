#pragma once
#include <assimp/camera.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const aiCamera* camera, aiNode * node);

	float m_FOV;
	float m_AR;
	glm::mat4 m_View;
	glm::vec3 m_Position;
	glm::vec3 lower_left_corner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
};

