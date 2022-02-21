#include <iostream>
#include "Image.hpp"
#include <Scene/Scene.h>
#include "print_helpers.h"
#include <future>
#include "Random.h"

const uint32_t MAX_DEPTH = 4;
const uint32_t SAMPLES_PER_PIXEL = 256;
const uint32_t IMG_WIDTH = 1080;
const float GAMMA = 2;

glm::vec3 rayColour(Ray& r, Scene& scene, int depth = 0) {
	glm::vec3 col(0);
	HitRecord rec;
	if (depth > MAX_DEPTH) {
		return glm::vec3(0);
	}
	if (scene.Intersect(r, rec, 0.1f, INFINITY)) {
		// Render normals
		//col = rec.normal * 0.5f + 0.5f;

		// Render Distance
		float min = 1000, max = 1500;
		//col = glm::vec3(1.0f - ((rec.t- min) / (max - min) ));

		// Base Colour
		//if (depth == MAX_DEPTH) {
		//	col = scene.GetMaterial(rec.mIndex).GetColour();
		//}
		//else {
			// Diffuse
			Ray r(rec.point, glm::normalize(rec.normal + Random::RandomUnitVector()));
			col = scene.GetMaterial(rec.mIndex).GetColour() * rayColour(r, scene, depth + 1);
		//}

	}
	else {
		float ratio = (-r.direction.y + 1.0f) / 2.0f;
		col = glm::vec3(1.0f) * ratio + glm::vec3(0.5f, 0.7f, 1.0f) * (1.0f - ratio);
	}
	return col;
}

glm::vec3 pixelColour(int x, int y, int width, int height, const Camera& camera, Scene& scene) {
	int samples_per_pixel = SAMPLES_PER_PIXEL;
	glm::vec3 col(0.0f);

	for (int s = 0; s < samples_per_pixel; s++) {
		Ray r = camera.GenerateRay(
			(x + Random::RandomFloat()) / static_cast<float>(width),
			(y + Random::RandomFloat()) / static_cast<float>(height));
		col += rayColour(r, scene);
	}

	float scale = 1.0f / static_cast<float>(samples_per_pixel);
	col *= scale;
	col.r = glm::pow(col.r, 1.0f / GAMMA);
	col.g = glm::pow(col.g, 1.0f / GAMMA);
	col.b = glm::pow(col.b, 1.0f / GAMMA);

	return col;
}



void renderScene(const char* sceneName, const char* outName) {

	Scene scene(sceneName);

	// Image output
	for (const Camera& camera : scene.GetCameras()) {
		unsigned int height = IMG_WIDTH, width = static_cast<unsigned int>(height * camera.AR);
		Image i(width, height);
		unsigned int thread_count = 4;
		std::vector<std::future<bool>> threads;
		std::atomic<unsigned int> index;
		auto executor = [&]() -> bool {
			unsigned int local_i = index++;
			while (local_i < width * height) {
				if (local_i % 500 == 0) {
					std::stringstream ss;

					ss << (local_i * 100) / (width * height) << "%" << std::endl;
					std::cout << ss.str();
				}
				unsigned int x = local_i % width;
				unsigned int y = local_i / width;
				i.WriteNormalizedColour(x, y, pixelColour(x, y, width, height, camera, scene));
				local_i = index++;
			}
			return true;
		};
		for (unsigned int thread = 0; thread < thread_count; thread++) {
			threads.push_back(std::async(std::launch::async, executor));
		}
		for (auto& thread : threads) {
			thread.wait();
		}
		i.Save(outName + camera.name);
	}
}

int main(int argc, char* argv[]) {
	Random::Init();
	try {
		renderScene("scenes/Basic.fbx", "output/out");
	}
	catch (const std::runtime_error & e){
		std::cerr << e.what() << std::endl;
		return 1;
	}

}