#pragma once
#include <Scene/Camera.h>
#include <Scene/Light.h>
#include <Scene/Mesh.h>
#include <Scene/Material.h>
#include <vector>
#include <memory>
#include <Ray.h>
#include <HitRecord.h>
#include "Hittable.hpp"
#include "HittableList.hpp"
#include <BVH/BVHNode.hpp>

class Scene: public Hittable
{
public:
	/*Load a scene from a file using Assimp*/
	Scene(const char* path);
	~Scene();

	const std::vector<Camera>& GetCameras() const;
	inline const Material& GetMaterial(int i) const {
		return m_Materials[i];
	}
	virtual bool Intersect(const Ray& r, HitRecord& rec, float min, float max) const;
	bool GetBounds(AABB& out) const;

private:
	std::vector<Camera> m_Cameras;
	std::vector<std::shared_ptr<Light>> m_Lights;
	std::vector<std::shared_ptr<Mesh>> m_Meshes;
	std::vector<Material> m_Materials;
	BVHNode m_BVH;
};

