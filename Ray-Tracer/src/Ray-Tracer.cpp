#include <iostream>
#include "Image.hpp"
#include <Scene/Scene.h>
#include "print_helpers.h"

void renderScene(const char* sceneName, const char* outName) {

	Scene scene(sceneName);
	unsigned int height = 1080, width = height * scene.GetCamera().m_AR;
	Image i(width, height);
	// Image output
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			Ray r = scene.GenerateRay(
				x / static_cast<float>(width - 1),
				y / static_cast<float>(height - 1));

			HitRecord rec;
			float dist;
			if (scene.Intersect(r, rec)) {
				i.at(x, y) = (rec.normal +1.0f) * 127.5f;
			}
			else {
				float ratio = (-r.direction.y + 1.0f) / 2.0f;
				i.at(x, y) = glm::vec3(255.0f) * ratio + glm::vec3(128, 190, 255) * (1 - ratio);
			}
		}
	}
	i.Save(outName);
}

int main(int argc, char* argv[]) {

	try {
		//renderScene("scenes/Basic.fbx", "output/out.png");
		//renderScene("scenes/Basic1.fbx", "output/out1.png");
		//renderScene("scenes/Basic2.fbx", "output/out2.png");
		renderScene("scenes/Basic3.fbx", "output/out3.png");
	
		std::cout << "Import successful" << std::endl;
	}
	catch (const std::runtime_error & e){
		std::cerr << e.what() << std::endl;
		return 1;
	}

}