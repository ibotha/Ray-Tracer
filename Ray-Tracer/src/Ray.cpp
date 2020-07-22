#include "Ray.h"

Ray Ray::Transform(const glm::mat4& matrix) const
{
	Ray ret;
	glm::vec4 tDirection = glm::vec4(direction.x, direction.y, direction.z, 0.0f) * matrix;
	glm::vec4 tOrigin = glm::vec4(origin.x, origin.y, origin.z, 1.0f) * matrix;

	ret.direction = { tDirection.x, tDirection.y, tDirection.z };
	ret.origin = { tOrigin.x, tOrigin.y, tOrigin.z };
	// TODO: Transformations
	return ret;
}
