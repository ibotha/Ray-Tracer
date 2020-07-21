#include "Object.h"
#include <glm/gtx/transform.hpp>

Object::Object(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
{
	transform = glm::rotate(
		glm::rotate(
			glm::rotate(
				glm::scale(
					glm::translate(
						glm::identity<glm::mat4>(), pos), scale
				), rot.y, glm::vec3(0, 1, 0)
			), rot.x, glm::vec3(1, 0, 0)
		), rot.z, glm::vec3(0, 0, 1)
	);

	invtransform = glm::inverse(transform);
}
