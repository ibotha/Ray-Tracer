#include <iostream>
#include "Image.hpp"
#include <Scene/Scene.h>
#include "print_helpers.h"
#include <glm/gtc/random.hpp>
#include <future>
#include <random>

const uint32_t MAX_DEPTH = 7;

inline float random_float() {
	static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	static std::mt19937 generator;
	return distribution(generator);
}

inline float random_float(float min, float max) {
	// Returns a random real in [min,max).
	return min + (max - min) * random_float();
}

inline glm::vec3 random_vec3() {
	return glm::vec3(random_float(), random_float(), random_float());
}

inline glm::vec3 random_vec3(float min, float max) {
	return glm::vec3(random_float(min, max), random_float(min, max), random_float(min, max));
}

glm::vec3 random_in_unit_sphere() {
	while (true) {
		auto p = random_vec3(-1, 1);
		if (glm::dot(p,p) >= 1) continue;
		return p;
	}
}

glm::vec3 rayColour(Ray& r, Scene& scene, int depth = 0) {
	glm::vec3 col(0);
	HitRecord rec;
	if (depth > MAX_DEPTH) {
		return glm::vec3(0);
	}
	if (scene.Intersect(r, rec, 0.001f, INFINITY)) {
		// Render normals
		//col = rec.normal * 0.5f + 0.5f;

		// Render Distance
		float min = 1000, max = 1500;
		//col = glm::vec3(1.0f - ((rec.t- min) / (max - min) ));

		// Diffuse
		Ray r(rec.point, glm::normalize(rec.normal + random_in_unit_sphere()));
		col = scene.GetMaterial(rec.mIndex).GetColour() * rayColour(r, scene, depth + 1);

		// Base Colour
		//col = scene.GetMaterial(rec.mIndex).GetColour();
	}
	else {
		float ratio = (-r.direction.y + 1.0f) / 2.0f;
		col = glm::vec3(1.0f) * ratio + glm::vec3(0.5f, 0.7f, 1.0f) * (1.0f - ratio);
	}
	return col;
}

glm::vec3 pixelColour(int x, int y, int width, int height, const Camera& camera, Scene& scene) {
	int samples_per_pixel = 200;
	glm::vec3 col(0.0f);

	for (int s = 0; s < samples_per_pixel; s++) {
		Ray r = camera.GenerateRay(
			(x + random_float()) / static_cast<float>(width),
			(y + random_float()) / static_cast<float>(height));
		col += rayColour(r, scene);
	}

	float scale = 1.0f / static_cast<float>(samples_per_pixel);
	col.r = glm::sqrt(scale * col.r);
	col.g = glm::sqrt(scale * col.g);
	col.b = glm::sqrt(scale * col.b);

	return col;
}



void renderScene(const char* sceneName, const char* outName) {

	Scene scene(sceneName);

	// Image output
	for (const Camera& camera : scene.GetCameras()) {
		unsigned int height = 256, width = static_cast<unsigned int>(height * camera.AR);
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
	srand(time(0));
	try {
		renderScene("scenes/Basic.fbx", "output/out");
	}
	catch (const std::runtime_error & e){
		std::cerr << e.what() << std::endl;
		return 1;
	}

}