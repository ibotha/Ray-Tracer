#pragma once
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

inline double random_double() {
	static std::uniform_real_distribution<double> distribution(0.0f, 1.0f);
	static std::mt19937 generator;
	return distribution(generator);
}

inline float random_float() {
	static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	static std::mt19937 generator;
	return distribution(generator);
}

inline double random_double_range(double min, double max) {
	return random_double()* (max - min) + min;
}

inline glm::vec3 random_in_unit_sphere()
{
	glm::vec3 ret;
	do
	{
		ret = { random_double_range(-1, 1),random_double_range(-1, 1) ,random_double_range(-1, 1) };
	} while (glm::length(ret) > 1.0f);
	return ret;
}

inline glm::vec3 random_unit_vector()
{
	auto a = random_double_range(0.0f, 2.0f * glm::pi<float>());
	auto z = random_double_range(-1, 1);
	auto r = glm::sqrt(1 - z * z);
	return glm::vec3(r * glm::cos(a), r * glm::sin(a), z);
}

inline glm::vec3 random_in_hemisphere(const glm::vec3& normal) {
	glm::vec3 in_unit_sphere = random_in_unit_sphere();
	if (glm::dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}