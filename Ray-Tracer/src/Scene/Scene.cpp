#include "Scene.h"
#include <stdexcept>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

Scene::Scene(const char* path)
{
	Assimp::Importer m_Importer{};
	const aiScene* scene = m_Importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	// If the import failed, report it
	if (!scene)
	{
		throw std::runtime_error(std::string("Import failed: ") + m_Importer.GetErrorString());
	}

	if (scene->HasCameras() == false) {
		throw std::runtime_error("Scene has no cameras!");
	}

	m_Camera = new Camera(scene->mCameras[0], scene->mRootNode->FindNode(scene->mCameras[0]->mName));

	if (scene->HasLights()) {
		m_Lights.reserve(scene->mNumLights);
		for (int i = 0; i < scene->mNumLights; i++)
		{
			m_Lights.push_back(Light::CreateLight(scene->mLights[i], scene->mRootNode->FindNode(scene->mLights[i]->mName)));
		}
	}

	if (scene->HasMeshes()) {
		m_Meshes.reserve(scene->mNumMeshes);
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			m_Meshes.emplace_back(scene->mMeshes[i], scene->mRootNode->FindNode(scene->mMeshes[i]->mName));
		}
	}
}

Scene::~Scene() {
	delete m_Camera;
}

Ray Scene::GenerateRay(float x, float y) const
{
	Ray ray{
		glm::vec3(0),
		glm::normalize(m_Camera->lower_left_corner + x* m_Camera->horizontal + y* m_Camera->vertical)
	};
	return ray.Transform(m_Camera->m_View);
}

const Camera& Scene::GetCamera() const
{
	return *m_Camera;
}

bool Scene::Intersect(const Ray& r, HitRecord&rec) const
{
	float closest = INFINITY;
	rec.t = INFINITY;
	for (const Mesh& mesh : m_Meshes) {
		HitRecord ret_rec;
		if (mesh.Intersect(r, ret_rec)) {
			if (ret_rec.t < rec.t)
				rec = ret_rec;
		}
	}
	return rec.t != INFINITY;
}
