#include "Mesh.h"
#include <conversion.h>
#include <print_helpers.h>
#include <glm/gtx/transform.hpp>
#include <HitRecord.h>

Mesh::Mesh(aiMesh* mesh, aiNode * node)
{
    m_Model = glm::inverse(aiGetNodeWorldMatrix(node));
	m_Vertices.reserve(mesh->mNumVertices);
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

bool Mesh::Intersect(const Ray& r, HitRecord& rec) const
{
    Ray local = r.Transform(m_Model);
    float radius = 22;
    float a = glm::dot(local.direction, local.direction);
    float b = 2.0f * glm::dot(local.origin, local.direction);
    float c = glm::dot(local.origin, local.origin) - radius*radius;
    float discriminant = b*b - 4*a*c;
    rec.colour = glm::vec3(1, 0.7, 0.5);
    if (discriminant > 0) {
        float dist = (-b - glm::sqrt(discriminant)) / (2.0f * a);
        if (dist > 0) {
            rec.t = dist;
            rec.point = r.At(dist);
            rec.normal = glm::normalize(glm::inverse(glm::mat3(m_Model)) * local.At(dist));
            return true;
        }
        dist = (-b + glm::sqrt(discriminant)) / (2.0f * a);
        if (dist > 0) {
            rec.t = dist;
            rec.point = r.At(dist);
            rec.normal = glm::normalize(glm::inverse(glm::mat3(m_Model)) * local.At(dist));
            return true;
        }
    }
    return false;
}
