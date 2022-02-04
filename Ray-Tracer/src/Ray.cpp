#include "Ray.h"
#include "print_helpers.h"

Ray::Ray(glm::vec3 _origin, glm::vec3 _direction)
{
	origin = _origin;
	direction = _direction;
}

Ray Ray::Transform(const glm::mat4& mat) const
{
	glm::vec3 new_origin = glm::vec3(glm::vec4(origin, 1) * mat);
	glm::vec3 new_direction = direction * glm::mat3(mat);
	return Ray(
		new_origin,
		new_direction
	);

}

std::ostream& operator<<(std::ostream& out, Ray r)
{
	return out << "Ray ( Origin: " << r.origin << ", Direction: " << r.direction << ")";
}
