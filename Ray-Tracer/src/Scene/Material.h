#pragma once
#include <assimp/material.h>
#include <glm/glm.hpp>

class Material
{
public:
	Material(aiMaterial* mat);
	inline const glm::vec3& GetColour()const { return m_Colour; }
private:
	glm::vec3 m_Colour = glm::vec3(0.8, 0.2, 0.8);
};

