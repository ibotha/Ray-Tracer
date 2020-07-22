#pragma once
#include "Camera.h"
#include <memory>
#include <Object.h>

class Scene
{
public:
	Scene();

	Intersection Intersect(const Ray& ray);
	Camera camera;
	std::vector<std::shared_ptr<Object>> objects;
};