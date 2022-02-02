#include "print_helpers.h"

std::ostream& operator<<(std::ostream& out, glm::vec3 v)
{
	return out << "Vec3 (" << v.x << ", " << v.y << ", " << v.z << ")";
}

std::ostream& operator<<(std::ostream& out, glm::vec4 v)
{
	return out << "Vec4 (" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
}

std::ostream& operator<<(std::ostream& out, glm::mat4 m)
{
	return out << "======== Mat4 ========" << std::endl
		<< m[0] << std::endl
		<< m[1] << std::endl
		<< m[2] << std::endl
		<< m[3] << std::endl
		<< "======================";
}