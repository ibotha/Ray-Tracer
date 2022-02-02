#pragma once
#include <assimp/camera.h>
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const aiCamera* camera);

	glm::mat4 m_Projection;
	glm::mat4 m_View;
	glm::mat4 m_ViewProjection;
	glm::vec3 m_Position;
};

