#include "Light.h"
#include <conversion.h>

std::unique_ptr<Light> Light::CreateLight(aiLight* light, aiNode* node) {
	switch (light->mType) {
	case aiLightSource_DIRECTIONAL:
		return std::make_unique<DirectionalLight>(light, node);
	case aiLightSource_POINT:
		return std::make_unique<PointLight>(light, node);
	default:
		return nullptr;
	}
}

Light::Light(aiLight* light) {
	m_Colour = aiCol3ToGLMVec3(light->mColorDiffuse);
}

DirectionalLight::DirectionalLight(aiLight* light, aiNode*node): Light(light){
	glm::mat4 transform = aiGetNodeWorldMatrix(node);
	m_Type = Light::Type::DIRECTIONAL;
	m_Direction = aiVec3DToGLMVec3(light->mDirection) * glm::mat3(transform);
}

PointLight::PointLight(aiLight* light, aiNode* node) : Light(light) {
	glm::mat4 transform = aiGetNodeWorldMatrix(node);
	m_Type = Light::Type::POINT;
	m_Position = glm::vec4(aiVec3DToGLMVec3(light->mPosition), 1.0f) * transform;
}