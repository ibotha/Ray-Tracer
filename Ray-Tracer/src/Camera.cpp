#include "Camera.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(const glm::vec3& pos, const glm::vec3& rot, float _FOV)
	:transform(glm::translate(pos) * glm::rotate(rot.y, glm::vec3(0, 1, 0)) * glm::rotate(rot.x, glm::vec3(1, 0, 0)))
{
	auto vecSep = ", ";
	std::cout << "Creating Camera. Position(" 
		<< pos.x << vecSep << pos.y << vecSep << pos.z 
		<< "), Rotation(" 
		<< rot.x << vecSep << rot.y << vecSep << rot.z << ")\n";
	FOV = glm::radians(_FOV);
}
