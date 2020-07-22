#pragma once
#include <random>
#include <glm/glm.hpp>

inline double random_double() {
	static std::uniform_real_distribution<double> distribution(0.0f, 1.0f);
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