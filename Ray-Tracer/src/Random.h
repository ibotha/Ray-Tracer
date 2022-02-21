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

	inline static float RandomFloat() {
		static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
		static std::mt19937 generator;
		return distribution(generator);
	}

	inline static float RandomFloat(float min, float max) {
		// Returns a random real in [min,max).
		return min + (max - min) * RandomFloat();
	}

	inline static glm::vec3 RandomVec3() {
		return glm::vec3(RandomFloat(), RandomFloat(), RandomFloat());
	}

	inline static glm::vec3 RandomVec3(float min, float max) {
		return glm::vec3(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
	}

	inline static glm::vec3 RandomInUnitSphere() {
		while (true) {
			auto p = RandomVec3(-1, 1);
			if (glm::dot(p, p) >= 1) continue;
			return p;
		}
	}

	inline static glm::vec3 RandomUnitVector() {
		return glm::normalize(RandomInUnitSphere());
	}
};

