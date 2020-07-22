#include "RayTracer.h"
#include "glm/gtc/constants.hpp"
#include <iostream>
#include "Camera.h"
#include "Ray.h"


RayTracer::RayTracer(const Scene& scene, int32_t w, int32_t h)
	:m_Scene(scene), m_Render(w, h)
{}

void RayTracer::render()
{
	float FOV = glm::radians(90.0f);
	const float AR = m_Render.height / static_cast<float>(m_Render.width);
	const float	invheight = 1.0f / static_cast<float>(m_Render.height);
	const float	invwidth = 1.0f / static_cast<float>(m_Render.width);
	const float	angle = glm::tan(FOV * 0.5f); // TODO: get FOV from camera

	for (int x = 0; x < m_Render.width; x++)
	{
		for (int y = 0; y < m_Render.height; y++)
		{
			Ray ray;
			ray.origin = { 0, 0, 0 };
			ray.direction = {
				(2 * x * invwidth - 1) * angle * (1 / AR),//(2.0f * ((float)x + 0.5f) * invwidth - 1.0f) * (float)m_Render.width * invheight * angle,
				((2 - 2 * y * invheight) - 1) * angle,//(1.0f - 2.0f * ((float)y + 0.5f) * invheight) * angle,
				-1.0f
			};
			ray.Normalize();

			m_Render.SetPixel(x, y, Trace(ray));
		}
	}
}

// Sends a ray out into the scene and returns the color after all lighting and other calculations
olc::Pixel RayTracer::Trace(const Ray& ray)
{
	//Intersection i = m_Scene.Intersect(ray);

	// if (i.hit)
		return olc::Pixel(
			0,//(ray.direction.x * 0.5 + 0.5) * 255,
			0,//(ray.direction.y * 0.5 + 0.5) * 255,
			0//(ray.direction.z * 0.5 + 0.5) * 255
		);
	//else
	//	return olc::Pixel(
	//		30,
	//		30,
	//		30
	//	);
}
