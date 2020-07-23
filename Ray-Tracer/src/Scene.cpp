#include "Scene.h"

Scene::Scene()
	:camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 60.0f)
{
}

Intersection Scene::Intersect(const Ray& ray, float min, float max)
{
	Intersection i;
	i.dist = INFINITY;

	for (auto o : objects)
	{
		Intersection n = o->Intersect(ray, min, max);
		n.object = o;
		if (n.hit)
		{
			max = n.dist;
			i = n;
		}
	}
	return i;
}
