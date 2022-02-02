#pragma once
#include <assimp/light.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <memory>

class Light
{
public:
	enum class Type
	{
		DIRECTIONAL,
		POINT,
		UNSUPPORTED
	};

	glm::vec3 m_Colour;
	Type m_Type = Type::UNSUPPORTED;
	static std::unique_ptr<Light> CreateLight(aiLight* light, aiNode* node);
	virtual ~Light() {}
protected:
	Light(aiLight* light);
};

class DirectionalLight : public Light {
public:
	glm::vec3 m_Direction;
	DirectionalLight(aiLight* light, aiNode* node);
};

class PointLight : public Light {
public:
	glm::vec3 m_Position;
	PointLight(aiLight* light, aiNode* node);
};

