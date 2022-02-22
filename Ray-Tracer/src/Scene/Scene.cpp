#include "Scene.h"
#include <stdexcept>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/gtc/random.hpp>
#include <Scene/BoundingBox.hpp>

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

	// Import Cameras
	for (unsigned int i = 0; i < scene->mNumCameras; i++)
	{
		m_Cameras.emplace_back(scene->mCameras[i], scene->mRootNode->FindNode(scene->mCameras[i]->mName));
	}

	// Import Lights
	if (scene->HasLights()) {
		m_Lights.reserve(scene->mNumLights);
		for (unsigned int i = 0; i < scene->mNumLights; i++)
		{
			m_Lights.push_back(Light::CreateLight(scene->mLights[i], scene->mRootNode->FindNode(scene->mLights[i]->mName)));
		}
	}

	// Import Meshes
	if (scene->HasMeshes()) {
		m_Meshes.reserve(scene->mNumMeshes);
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			m_Meshes.emplace_back(std::make_shared<Mesh>(scene->mMeshes[i], scene->mRootNode->FindNode(scene->mMeshes[i]->mName)));
		}
	}

	// Import Materials
	if (scene->HasMaterials()) {
		m_Materials.reserve(scene->mNumMaterials);
		for (unsigned int i = 0; i < scene->mNumMaterials; i++)
		{
			m_Materials.emplace_back(scene->mMaterials[i]);
		}
	}

	std::sort(m_Meshes.begin(), m_Meshes.end(), [](auto& a, auto& b)-> int {
		AABB a_bound, b_bound;
		a->GetBounds(a_bound);
		b->GetBounds(b_bound);
		return glm::distance(a_bound.min, glm::vec3(0.0f)) - glm::distance(b_bound.min, glm::vec3(0.0f));
		});

	std::vector<std::shared_ptr<Hittable>> meshes_as_hittable;
	for (auto& a : m_Meshes)
		meshes_as_hittable.push_back(a);

	// Construct AABBs
	//m_Hittables = meshes_as_hittable;
	m_BVH = BVHNode(meshes_as_hittable, 0, meshes_as_hittable.size());
	std::cout << "Heirarchy Constructed!\n";
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
	if (m_BVH.Intersect(r, local_rec, min, max) ) {
		if (local_rec.t < rec.t) {
			rec = local_rec;
		}
	}
	return rec.t != INFINITY;
}

bool Scene::GetBounds(AABB& out) const
{
	m_BVH.GetBounds(out);
	return true;
}
