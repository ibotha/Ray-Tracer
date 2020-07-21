#pragma once
#include "Scene.h"

class RayTracer
{
public:
	RayTracer(const Scene& scene);

	void render();
private:
	Scene m_Scene;
};