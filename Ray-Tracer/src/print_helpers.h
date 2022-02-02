#pragma once
#include <iostream>
#include <glm/glm.hpp>

std::ostream& operator<<(std::ostream& out, glm::vec3 v);
std::ostream& operator<<(std::ostream& out, glm::vec4 v);
std::ostream& operator<<(std::ostream& out, glm::mat4 m);