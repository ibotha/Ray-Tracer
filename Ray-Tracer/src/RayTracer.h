#pragma once
#include "Scene.h"
#include <Ray.h>
#include <glm/glm.hpp>
#include "olcPixelGameEngine.h"
#include <vector>

class RayTracer
{
public:
	RayTracer(const Scene& scene, int32_t w, int32_t h);

	void render();

	inline olc::Sprite& GetRender() { return m_Render; }
	inline Scene& GetScene() { return m_Scene; }

	olc::Pixel Trace(const Ray& ray);

private:
	Scene m_Scene;
	olc::Sprite m_Render;
};