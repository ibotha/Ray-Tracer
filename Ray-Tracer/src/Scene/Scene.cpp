#include "Scene.h"
#include <stdexcept>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/gtc/random.hpp>

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

	for (unsigned int i = 0; i < scene->mNumCameras; i++)
	{
		m_Cameras.emplace_back(scene->mCameras[i], scene->mRootNode->FindNode(scene->mCameras[i]->mName));
	}

	if (scene->HasLights()) {
		m_Lights.reserve(scene->mNumLights);
		for (unsigned int i = 0; i < scene->mNumLights; i++)
		{
			m_Lights.push_back(Light::CreateLight(scene->mLights[i], scene->mRootNode->FindNode(scene->mLights[i]->mName)));
		}
	}

	if (scene->HasMeshes()) {
		m_Meshes.reserve(scene->mNumMeshes);
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			m_Meshes.emplace_back(scene->mMeshes[i], scene->mRootNode->FindNode(scene->mMeshes[i]->mName));
		}
	}

	if (scene->HasMaterials()) {
		m_Materials.reserve(scene->mNumMaterials);
		for (unsigned int i = 0; i < scene->mNumMaterials; i++)
		{
			m_Materials.emplace_back(scene->mMaterials[i]);
		}
	}
}

Scene::~Scene() {
}

const std::vector<Camera>& Scene::GetCameras() const
{
	return m_Cameras;
}

bool Scene::Intersect(const Ray& r, HitRecord& rec, float min, float max) const
{
	HitRecord local_rec;
	rec.t = INFINITY;
	for (const Mesh& mesh : m_Meshes) {
		if (mesh.Intersect(r, local_rec, min, max) ) {
			if (local_rec.t < rec.t)
				rec = local_rec;
		}
	}
	return rec.t != INFINITY;
}
