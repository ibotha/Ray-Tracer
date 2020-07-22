#include "Scene.h"

Scene::Scene()
	:camera({0, 0, 0}, {0, 0, 0})
{
}

Intersection Scene::Intersect(const Ray& ray)
{
	Intersection i;
	i.dist = INFINITY;

	for (auto o : objects)
	{
		Intersection n = o->Intersect(ray);
		if (n.hit && n.dist < i.dist)
			i = n;
	}
	return i;
}
