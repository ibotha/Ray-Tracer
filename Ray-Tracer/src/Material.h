#pragma once
#include <glm/glm.hpp>
#include "Intersection.h"

class Material
{
public:

	virtual bool scatter(const Ray& in, const Intersection& intersection, glm::vec3& attenuation, Ray& scattered) = 0;
};

class Diffuse : public Material
{
public:
	glm::vec3 diffuseColor;
	float roughness;

	Diffuse(const glm::vec3& _diffuseColour, float _roughness);

	virtual bool scatter(const Ray& in, const Intersection& intersection, glm::vec3& attenuation, Ray& scattered) override;
};

class Metal : public Material
{
public:
	glm::vec3 color;
	float roughness;

	Metal(const glm::vec3& _color, float _roughness);

	virtual bool scatter(const Ray& in, const Intersection& intersection, glm::vec3& attenuation, Ray& scattered) override;
};

class Dielectric : public Material
{
public:
	glm::vec3 color;
	float roughness;
	float ri;

	Dielectric(const glm::vec3& _color, float _roughness, float _ri);

	virtual bool scatter(const Ray& in, const Intersection& intersection, glm::vec3& attenuation, Ray& scattered) override;
};