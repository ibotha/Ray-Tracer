#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(const glm::vec3& pos, const glm::vec3& rot)
{
	transform = glm::rotate(
		glm::rotate(
			glm::rotate(
				glm::translate(
					glm::identity<glm::mat4>(), pos
				), rot.y, glm::vec3(0, 1, 0)
			), rot.x, glm::vec3(1, 0, 0)
		), rot.z, glm::vec3(0, 0, 1)
	);

	FOV = glm::radians(90.0f);

	invtransform = glm::inverse(transform);
}
