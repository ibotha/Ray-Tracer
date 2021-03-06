#pragma once
#include "Scene.h"
#include <Ray.h>
#include <glm/glm.hpp>
#include "olcPixelGameEngine.h"
#include <vector>

class RayTracer
{
public:
	RayTracer(int32_t w, int32_t h, int max_depth = 3, int samplesPerPixel = 16);

	void RenderParallel();

	void Render();

	inline olc::Sprite& GetRender() { return m_Render; }
	inline olc::Sprite& GetDepth() { return m_Depth; }
	inline Scene& GetScene() { return m_Scene; }

	glm::vec3 Trace(const Ray& ray, int depth = 0);

	void RenderDepth();

	int TraceDepth(const Ray& ray, int depth);


private:
	int max_depth = 3;
	float samplesPerPixel = 16;
	Scene m_Scene;
	olc::Sprite m_Render;
	olc::Sprite m_Depth;
};