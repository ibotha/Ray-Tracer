#include <iostream>
#include "Image.hpp"
#include <Scene/Scene.h>
#include "print_helpers.h"
#include <glm/gtc/random.hpp>

glm::vec3 rayColour(Ray& r, Scene& scene, int depth = 0) {
	glm::vec3 col(0);
	HitRecord rec;
	if (depth == 25) {
		return glm::vec3(0);
	}
	if (scene.Intersect(r, rec, 2.f, INFINITY)) {
		// Render normals
		//col = rec.normal * 0.5f + 0.5f;

		// Render Distance
		float min = 1000, max = 2000;
		//col = glm::vec3(1.0f - ((rec.t- min) / (max - min) ));

		// Diffuse
		Ray r(rec.point, glm::normalize(rec.normal + glm::sphericalRand(1.0f)));
		col = scene.GetMaterial(rec.mIndex).GetColour() * rayColour(r, scene, depth + 1);
	}
	else {
		float ratio = (-r.direction.y + 1.0f) / 2.0f;
		col = glm::vec3(1.0f) * ratio + glm::vec3(0.5f, 0.7f, 1.0f) * (1.0f - ratio);
	}
	return col;
}

glm::vec3 pixelColour(int x, int y, int width, int height, const Camera& camera, Scene& scene) {
	int samples_per_pixel = 100;
	glm::vec3 col(0.0f);

	for (int s = 0; s < samples_per_pixel; s++) {
		Ray r = camera.GenerateRay(
			(x + glm::linearRand<float>(0, 1.0f)) / static_cast<float>(width),
			(y + glm::linearRand<float>(0, 1.0f)) / static_cast<float>(height));
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
		for (unsigned int x = 0; x < width; x++) {
			//std::cout << (x * 100) / static_cast<float>(width) << "%" << std::endl;
			for (unsigned int y = 0; y < height; y++) {
				glm::vec3 col = pixelColour(x, y, width, height, camera, scene);

				i.WriteNormalizedColour(x, y, col);
			}
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