#pragma once
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <vector>
#include <glm/glm.hpp>

class Mesh
{
public:
	Mesh(aiMesh* mesh, aiNode* node);

private:
	glm::vec3 m_Position;
	glm::mat4 m_Model;
	std::vector<glm::vec3> m_Vertices;
	std::vector<unsigned int> m_Indices;
};

