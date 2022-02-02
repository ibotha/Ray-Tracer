#include <iostream>
#include "Image.hpp"
#include <Scene/Scene.h>

int main(int argc, char* argv[]) {

	try {
		Scene scene("scenes/Basic.fbx");
		// Image output
		Image i(1080, 1080);
		for (int x = 0; x < 1080; x++) {
			for (int y = 0; y < 1080; y++) {
				scene.
				i.at(x, y) = colour{
					static_cast<unsigned char>((x * 255) / 1080),
					0,
					static_cast<unsigned char>((y * 255) / 1080)
				};
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