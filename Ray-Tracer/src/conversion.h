#pragma once
#include <assimp/vector3.h>
#include <assimp/matrix4x4.h>
#include <assimp/types.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>

glm::vec3 aiVec3DToGLMVec3(const aiVector3D& vIn);
glm::vec3 aiCol3ToGLMVec3(const aiColor3D& vIn);
glm::mat4 aiMat4ToGLMMat4(const aiMatrix4x4& mIn);
glm::mat4 aiGetNodeWorldMatrix(aiNode* node);