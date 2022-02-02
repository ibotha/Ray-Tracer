#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

Image::Image(int width, int height):
	m_Width(width), m_Height(height)
{
	m_Data = new colour[(m_Width * m_Height)];
}

void Image::Save(const char* path)
{
	stbi_flip_vertically_on_write(true);
	stbi_write_png(path, m_Width, m_Height, 3, m_Data, m_Width * 3);
}

colour & Image::at(int x, int y)
{
	return m_Data[x + m_Width * y];
}

Image::~Image() {
	delete[] m_Data;
}
