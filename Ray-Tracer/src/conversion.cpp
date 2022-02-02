#include "conversion.h"

glm::vec3 aiVec3DToGLMVec3(const aiVector3D& vIn) {
	return glm::vec3(vIn.x, vIn.y, vIn.z);
}

glm::vec3 aiCol3ToGLMVec3(const aiColor3D& vIn)
{
	return glm::vec3(vIn.r, vIn.g, vIn.b);
}
