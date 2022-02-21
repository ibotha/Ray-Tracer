#pragma once
#include <assimp/material.h>
#include <glm/glm.hpp>
#include <Ray.h>
#include <HitRecord.h>

class Material
{
public:
	Material(aiMaterial* mat);
	inline const glm::vec3& GetDiffuse()const { return m_Diffuse; }
	inline const glm::vec3& GetEmission()const { return m_Emission; }
	inline const glm::vec3& GetSpecular()const { return m_Specular; }
	inline const glm::vec3& GetReflective()const { return m_Reflective; }
	inline const glm::vec3& GetAmbient()const { return m_Ambient; }
	inline const float GetShininess()const { return m_Shininess; }
	inline const float GetShininessStrength()const { return m_ShininessStrength; }
	inline const bool IsEmissive()const { return m_Emissive; }

	bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const;
private:
	glm::vec3 m_Diffuse = glm::vec3(0);
	glm::vec3 m_Emission = glm::vec3(0);
	glm::vec3 m_Specular = glm::vec3(0);
	glm::vec3 m_Reflective = glm::vec3(0);
	glm::vec3 m_Ambient = glm::vec3(0);
	glm::vec3 m_Transparent = glm::vec3(0);
	float m_Shininess{ 0 };
	float m_ShininessStrength{ 0 };
	float m_Reflectivity{ 0 };
	float m_RefractionIndex{ 0 };
	float m_Transmission{ 0 };
	bool m_Emissive = false;
	bool m_Gloss = false;
};

