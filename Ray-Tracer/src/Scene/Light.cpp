#include "Light.h"
#include <conversion.h>

std::unique_ptr<Light> Light::CreateLight(aiLight* light) {
	switch (light->mType) {
	case aiLightSource_DIRECTIONAL:
		return std::make_unique<DirectionalLight>(light);
	case aiLightSource_POINT:
		return std::make_unique<PointLight>(light);
	default:
		return nullptr;
	}
}

Light::Light(aiLight* light) {
	m_Colour = aiCol3ToGLMVec3(light->mColorDiffuse);
}

DirectionalLight::DirectionalLight(aiLight* light): Light(light){
	m_Type = Light::Type::DIRECTIONAL;
	m_Direction = aiVec3DToGLMVec3(light->mDirection);
}

PointLight::PointLight(aiLight* light) : Light(light) {
	m_Type = Light::Type::POINT;
	m_Position = aiVec3DToGLMVec3(light->mPosition);
}