#include "conversion.h"
#include <iostream>
#include "print_helpers.h"


glm::vec3 aiVec3DToGLMVec3(const aiVector3D& vIn) {
	return glm::vec3(vIn.x, vIn.y, vIn.z);
}

glm::vec3 aiCol3ToGLMVec3(const aiColor3D& vIn)
{
	return glm::vec3(vIn.r, vIn.g, vIn.b);
}

glm::mat4 aiMat4ToGLMMat4(const aiMatrix4x4& mIn)
{
	glm::mat4 m;
	m[0][0] = mIn[0][0];
	m[0][1] = mIn[0][1];
	m[0][2] = mIn[0][2];
	m[0][3] = mIn[0][3];

	m[1][0] = mIn[1][0];
	m[1][1] = mIn[1][1];
	m[1][2] = mIn[1][2];
	m[1][3] = mIn[1][3];

	m[2][0] = mIn[2][0];
	m[2][1] = mIn[2][1];
	m[2][2] = mIn[2][2];
	m[2][3] = mIn[2][3];

	m[3][0] = mIn[3][0];
	m[3][1] = mIn[3][1];
	m[3][2] = mIn[3][2];
	m[3][3] = mIn[3][3];


	return m;
}

glm::mat4 aiGetNodeWorldMatrix(aiNode* node)
{
	glm::mat4 ret = aiMat4ToGLMMat4(node->mTransformation);
	while (node->mParent != nullptr) {
		node = node->mParent;
		glm::mat4 transform = aiMat4ToGLMMat4(node->mTransformation);
		ret = ret * transform;
	}
	return ret;
}
