#pragma once
#include <glm/glm.hpp>
#include <string>
typedef glm::u8vec3 colour;

class Image
{
public:

	Image(int width, int height);
	~Image();
	void Save(const std::string& path);

	colour& At(int x, int y);

	/*Writes a colour that is defined by values between 0 and 1*/
	void WriteNormalizedColour(int x, int y, const glm::vec3& colour);

private:
	colour* m_Data;
	int m_Width, m_Height;

};

