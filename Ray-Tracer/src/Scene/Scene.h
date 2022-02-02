#pragma once
#include <Scene/Camera.h>
#include <Scene/Light.h>
#include <Scene/Mesh.h>
#include <vector>
#include <memory>
#include <Ray.h>

class Scene
{
public:
	/*Load a scene from a file using Assimp*/
	Scene(const char* path);
	~Scene();

	/*Generates a ray in world space using the scenes camera.
	the x and y are between -1 and 1 where -1 is left and bottom*/
	Ray GenerateRay(float x, float y);
	const Camera& GetCamera()const;
private:
	Camera* m_Camera = nullptr;
	std::vector<std::unique_ptr<Light>> m_Lights;
	std::vector<Mesh> m_Meshes;
};

