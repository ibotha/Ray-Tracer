#include <iostream>
#include "Image.hpp"
#include <Scene/Scene.h>
#include "print_helpers.h"

int main(int argc, char* argv[]) {

	try {
		Scene scene("scenes/Basic.fbx");
		// Image output

		Ray r = scene.GenerateRay(0, 0);
		unsigned int height = 1080, width = height * scene.GetCamera().m_AR;
		Image i(width, height);
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				Ray r = scene.GenerateRay(
					(x - width / 2.0f) / static_cast<float>(width - 1),
					(y - height / 2.0f) / static_cast<float>(height - 1));
				i.at(x, y) = colour(
					r.direction * 127.5f + 127.4f
				);
			}
		}
		i.Save("output/out.png");
	
		std::cout << "Import successful" << std::endl;
	}
	catch (const std::runtime_error & e){
		std::cerr << e.what() << std::endl;
		return 1;
	}

}