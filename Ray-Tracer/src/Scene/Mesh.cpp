#include "Mesh.h"
#include <conversion.h>
#include <glm/gtx/transform.hpp>

Mesh::Mesh(aiMesh* mesh)
{
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
