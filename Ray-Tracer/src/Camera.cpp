#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(const glm::vec3& pos, const glm::vec3& rot)
	:transform(glm::translate(pos) * glm::rotate(rot.y, glm::vec3(0, 1, 0)) * glm::rotate(rot.x, glm::vec3(1, 0, 0)))
{
	FOV = glm::radians(60.0f);
}
