#pragma once
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <vector>
#include <glm/glm.hpp>
#include <Ray.h>
#include "HitRecord.h"
#include "Hittable.hpp"
#include "AABB.hpp"

class Mesh : public Hittable
{
public:
	Mesh(aiMesh* mesh, aiNode* node);
	bool Intersect(const Ray& r, HitRecord& rec, float min, float max) const;
	bool GetBounds(AABB & out) const;

	inline int GetMaterialIndex() { return m_MaterialIndex; }


private:
	glm::mat4 m_Model;
	std::vector<glm::vec3> m_Vertices;
	std::vector<unsigned int> m_Indices;
	AABB m_AABB;
	int m_MaterialIndex;
};

