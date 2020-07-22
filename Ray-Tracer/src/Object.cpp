#include "Object.h"
#include <glm/gtx/transform.hpp>

Object::Object(const Transform& _transform)
	:transform(_transform), mat(std::make_shared<Diffuse>(glm::vec3(0.5f), 0.8f))
{

}
