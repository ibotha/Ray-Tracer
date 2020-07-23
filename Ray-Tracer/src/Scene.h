#pragma once
#include "Camera.h"
#include <memory>
#include <vector>
#include <Object.h>

class Scene
{
public:
	Scene();

	Intersection Intersect(const Ray& ray, float min, float max);
	Camera camera;
	std::vector<std::shared_ptr<Object>> objects;
};