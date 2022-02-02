#include "Ray.h"
#include "print_helpers.h"

Ray Ray::Transform(const glm::mat4& mat)
{
	return Ray{
		glm::vec3(glm::vec4(origin, 1) * mat),
		glm::normalize(direction * glm::mat3(mat)),
	};
}

std::ostream& operator<<(std::ostream& out, Ray r)
{
	return out << "Ray ( Origin: " << r.origin << ", Direction: " << r.direction << ")";
}
