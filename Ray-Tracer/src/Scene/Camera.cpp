#include "Camera.h"
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <conversion.h>

Camera::Camera(const aiCamera* camera)
{
	m_Projection = glm::perspective(camera->mHorizontalFOV, 1.0f, camera->mClipPlaneNear, camera->mClipPlaneFar);
	m_Position = aiVec3DToGLMVec3(camera->mPosition);
	m_View = glm::lookAt(m_Position,
		aiVec3DToGLMVec3(camera->mLookAt)- m_Position,
		aiVec3DToGLMVec3(camera->mUp));
	m_ViewProjection = m_View * m_Projection;
}
