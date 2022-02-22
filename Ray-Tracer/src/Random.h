#pragma once
#include <random>
#include <glm/glm.hpp>
#include <ctime>


class Random
{
public:
	inline static void Init() {
		std::srand(time(0));
	}

	inline static float Float() {
		static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
		static std::mt19937 generator;
		return distribution(generator);
	}

	inline static float Float(float min, float max) {
		// Returns a random real in [min,max).
		return min + (max - min) * Float();
	}

	inline static int Int(int min, int max) {
		// Returns a random integer in [min,max).
		return min + (max - min) * Float();
	}

	inline static glm::vec3 Vec3() {
		return glm::vec3(Float(), Float(), Float());
	}

	inline static glm::vec3 Vec3(float min, float max) {
		return glm::vec3(Float(min, max), Float(min, max), Float(min, max));
	}

	inline static glm::vec3 InUnitSphere() {
		while (true) {
			auto p = Vec3(-1, 1);
			if (glm::dot(p, p) >= 1) continue;
			return p;
		}
	}

	inline static glm::vec3 UnitVector() {
		return glm::normalize(InUnitSphere());
	}

	inline static glm::vec3 InUnitDisk() {
		while (true) {
			auto p = glm::vec3(Float(-1, 1), Float(-1, 1), 0);
			if (glm::dot(p,p) >= 1) continue;
			return p;
		}
	}
};

