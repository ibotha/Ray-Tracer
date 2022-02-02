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

	/*if (scene->HasLights()) {
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
	}*/
}

Scene::~Scene() {
	delete m_Camera;
}

Ray Scene::GenerateRay(float x, float y)
{
	x = x * 2;
	y = y * 2;
	Ray ray{
		glm::vec3(0),
		glm::normalize(m_Camera->lower_left_cornder + x* m_Camera->horizontal + y* m_Camera->vertical)
	};
	return ray.Transform(m_Camera->m_View);
}

const Camera& Scene::GetCamera() const
{
	return *m_Camera;
}
