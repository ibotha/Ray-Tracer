#pragma once
#include <assimp/vector3.h>
#include <assimp/types.h>
#include <glm/glm.hpp>

glm::vec3 aiVec3DToGLMVec3(const aiVector3D& vIn);
glm::vec3 aiCol3ToGLMVec3(const aiColor3D& vIn);