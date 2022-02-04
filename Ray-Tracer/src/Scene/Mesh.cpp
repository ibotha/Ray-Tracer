#include "Mesh.h"
#include <conversion.h>
#include <print_helpers.h>
#include <glm/gtx/transform.hpp>
#include <HitRecord.h>

Mesh::Mesh(aiMesh* mesh, aiNode * node)
{
    m_Model = glm::inverse(aiGetNodeWorldMatrix(node));
    std::cout << m_Model << std::endl;
	m_Vertices.reserve(mesh->mNumVertices);
    m_MaterialIndex = mesh->mMaterialIndex;
	for (int i = 0; i < mesh->mNumVertices; i++) {
		m_Vertices.push_back(aiVec3DToGLMVec3(mesh->mVertices[i]));
	}

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const aiFace& Face = mesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        m_Indices.push_back(Face.mIndices[0]);
        m_Indices.push_back(Face.mIndices[1]);
        m_Indices.push_back(Face.mIndices[2]);
    }
}

float length_squared(glm::vec3 vec) {
    return glm::dot(vec, vec);
}

bool Mesh::Intersect(const Ray& r, HitRecord& rec, float min, float max) const
{
    Ray local = r.Transform(m_Model);
    float radius = 100;
    float a = length_squared(local.direction);
    float half_b = glm::dot(local.origin, local.direction);
    float c = length_squared(local.origin) - radius*radius;
    float discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    
    float sqrt_dis = glm::sqrt(discriminant);
    float dist = (-half_b - sqrt_dis) / a;
    if (dist < min || dist > max) {
        dist = (-half_b + sqrt_dis) / a;
        if (dist < min || dist > max) {
            return false;
        }
    }

    rec.t = dist;
    rec.mIndex = m_MaterialIndex;
    rec.SetNormal(r, glm::normalize(glm::inverse(glm::mat3(m_Model)) * local.At(dist)));
    rec.point = r.At(dist);
    return true;
}
