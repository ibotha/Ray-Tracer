#pragma once
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <vector>
#include <glm/glm.hpp>
#include <Ray.h>
#include "HitRecord.h"

class Mesh
{
public:
	Mesh(aiMesh* mesh, aiNode* node);
	bool Intersect(const Ray& r, HitRecord& rec, float min, float max) const;
	inline int GetMaterialIndex() { return m_MaterialIndex; }


private:
	glm::mat4 m_Model;
	std::vector<glm::vec3> m_Vertices;
	std::vector<unsigned int> m_Indices;
	int m_MaterialIndex;
};

