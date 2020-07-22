#include "Scene.h"

Scene::Scene()
	:camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 60.0f)
{
}

Intersection Scene::Intersect(const Ray& ray)
{
	Intersection i;
	i.dist = INFINITY;

	for (auto o : objects)
	{
		Intersection n = o->Intersect(ray);
		n.object = o;
		if (n.hit && n.dist < i.dist)
			i = n;
	}
	return i;
}
