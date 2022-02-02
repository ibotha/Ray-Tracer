#pragma once
#include <Scene/Scene.h>
#include <Image.hpp>

class RenderMethodInterface {
public:
	virtual void Render(const Scene& scene, Image& output) = 0;
};