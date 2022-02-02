#pragma once
#include <glm/glm.hpp>
typedef glm::u8vec3 colour;

class Image
{
public:
	struct Colour {
		unsigned char red;
		unsigned char blue;
		unsigned char green;
	};

	Image(int width, int height);
	~Image();
	void Save(const char* path);

	colour& at(int x, int y);

private:
	colour* m_Data;
	int m_Width, m_Height;

};

