#include "Material.h"
#include <iostream>
#include <print_helpers.h>
#include <conversion.h>
#include <Random.h>
bool almost_zero(const glm::vec3& v) {
	float eps = 1e-5f;
	return (v.x < eps&& v.y < eps&& v.z < eps);
}

Material::Material(aiMaterial* mat) {
	std::cout << mat->GetName().C_Str() << std::endl;

	for (unsigned int i = 0; i < mat->mNumProperties; i++)
	{
		std::cout << mat->mProperties[i]->mKey.C_Str() << ", ";
		switch (mat->mProperties[i]->mType)
		{
		case aiPTI_Float:
			glm::vec4 out(-1);
			memcpy(&out.x, mat->mProperties[i]->mData, mat->mProperties[i]->mDataLength);
			std::cout << out;
			break;
		default:
			break;
		}
		std::cout << std::endl;
	}

	aiColor3D diffuse(0);
	aiColor3D emission(0);
	aiColor3D specular(0);
	aiColor3D reflective(0);
	aiColor3D ambient(0);
	aiColor3D transparent(0);
	float shininess{0};
	float shininess_strength{ 0 };
	float shininess_tint{ 0 };
	float reflectivity{ 0 };
	float refraction_index{ 0 };
	float transmission{ 0 };

	if (mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) != aiReturn_SUCCESS) {
		std::cerr << "Diffuse Colour could not be read!" << std::endl;
	}

	if (mat->Get(AI_MATKEY_COLOR_EMISSIVE, emission) != aiReturn_SUCCESS) {
		std::cerr << "Emissive Colour could not be read!" << std::endl;
	}

	if (mat->Get(AI_MATKEY_COLOR_SPECULAR, specular) != aiReturn_SUCCESS) {
		std::cerr << "Specular colour could not be read!" << std::endl;
	}

	if (mat->Get(AI_MATKEY_COLOR_REFLECTIVE, reflective) != aiReturn_SUCCESS) {
		std::cerr << "reflective colour could not be read!" << std::endl;
	}

	if (mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient) != aiReturn_SUCCESS) {
		std::cerr << "reflective colour could not be read!" << std::endl;
	}

	if (mat->Get(AI_MATKEY_SHININESS, shininess) != aiReturn_SUCCESS) {
		std::cerr << "shininess could not be read!" << std::endl;
	}

	if (mat->Get(AI_MATKEY_SHININESS_STRENGTH, shininess_strength) != aiReturn_SUCCESS) {
		std::cerr << "shininess strength could not be read!" << std::endl;
	}
	
	if (mat->Get(AI_MATKEY_REFLECTIVITY, reflectivity) != aiReturn_SUCCESS) {
		std::cerr << "reflectivity could not be read!" << std::endl;
	}

	if (mat->Get("$raw.ior", 0, 0, refraction_index) != aiReturn_SUCCESS) {
		std::cerr << "refractive index could not be read!" << std::endl;
	}

	if (mat->Get("$raw.transmission", 0, 0, transmission) != aiReturn_SUCCESS) {
		std::cerr << "transmission could not be read!" << std::endl;
	}

	if (mat->Get("$raw.specular_tint", 0, 0, shininess_tint) != aiReturn_SUCCESS) {
		std::cerr << "specular_tint could not be read!" << std::endl;
	}

	if (mat->Get(AI_MATKEY_COLOR_TRANSPARENT, transparent) != aiReturn_SUCCESS) {
		std::cerr << "transparent could not be read!" << std::endl;
	}

	m_Diffuse = aiCol3ToGLMVec3(diffuse);
	m_Emission = aiCol3ToGLMVec3(emission);
	m_Specular = aiCol3ToGLMVec3(specular);
	m_Reflective = aiCol3ToGLMVec3(reflective);
	m_Ambient = aiCol3ToGLMVec3(ambient);
	m_Transparent = aiCol3ToGLMVec3(transparent);
	m_Shininess = shininess / 100.0f;
	m_ShininessStrength = shininess_strength;
	m_Roughness = 1 - m_Shininess;
	m_ShininessStrength = shininess_strength;
	m_SpecularTint = shininess_tint;
	m_Reflectivity = reflectivity;
	m_RefractionIndex = refraction_index;
	m_Transmission = transmission;
	m_Emissive = !almost_zero(m_Emission);
	m_Gloss = m_ShininessStrength > 1e-5;
	std::cout <<
		"m_Diffuse: " << m_Diffuse << std::endl <<
		"m_Emission: " << m_Emission << std::endl <<
		"m_Specular: " << m_Specular << std::endl <<
		"m_Reflective: " << m_Reflective << std::endl <<
		"m_Ambient: " << m_Ambient << std::endl <<
		"m_Transparent: " << m_Transparent << std::endl <<
		"m_Shininess: " << m_Shininess << std::endl <<
		"m_ShininessStrength: " << m_ShininessStrength << std::endl <<
		"m_SpecularTint: " << m_SpecularTint << std::endl <<
		"m_Reflectivity: " << m_Reflectivity << std::endl <<
		"m_Roughness: " << m_Roughness << std::endl <<
		"m_RefractionIndex: " << m_RefractionIndex << std::endl <<
		"m_Transmission: " << m_Transmission << std::endl <<
		"m_Emissive: " << m_Emissive << std::endl <<
		std::endl;
}


glm::vec3 Refract(const glm::vec3& uv, const glm::vec3& n, float etai_over_etat) {
	float cos_theta = fmin(dot(-uv, n), 1.0f);
	glm::vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	glm::vec3 r_out_parallel = -sqrt(fabs(1.0f - glm::dot(r_out_perp, r_out_perp))) * n;
	return r_out_perp + r_out_parallel;
}

float Reflectance(float cosine, float ref_idx) {
	// Use Schlick's approximation for reflectance.
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool Material::Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const
{
	scattered.origin = rec.point;

	// Reflect | Metalic
	if (Random::RandomFloat() < m_Reflectivity) {
		glm::vec3 reflected = glm::reflect(glm::normalize(in.direction), rec.normal) + (Random::RandomInUnitSphere() * m_Roughness);
		if (glm::dot(reflected, rec.normal) < 0)
			return false;
		scattered.direction = reflected;
		attenuation = m_Reflective;
		return true;
	}

	// Dielectric
	if (Random::RandomFloat() < m_Transmission) {
		float refraction_ratio = rec.inside ? m_RefractionIndex : (1 / m_RefractionIndex);

		glm::vec3 unit_direction = glm::normalize(in.direction);
		float cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0f);
		float sin_theta = sqrt(1.0f - cos_theta * cos_theta);
		bool refract = true;
		if ((refraction_ratio * sin_theta) > 1.0f) {
			refract = false;
		}
		else {
			refract = Reflectance(cos_theta, refraction_ratio) < Random::RandomFloat();
		}

		if (refract) {
			scattered.direction = glm::normalize(glm::refract(unit_direction, rec.normal, refraction_ratio) + (Random::RandomInUnitSphere() * m_Roughness));
			attenuation = m_Diffuse;
			return true;
		}
		glm::vec3 reflected = glm::normalize(glm::reflect(glm::normalize(in.direction), rec.normal) + (Random::RandomInUnitSphere() * m_Roughness));
		if (glm::dot(reflected, rec.normal) < 0)
			return false;
		scattered.direction = reflected;
		attenuation = m_Specular;
		return true;

	}


	// Reflect | Gloss
	if (Random::RandomFloat() < m_ShininessStrength) {

		glm::vec3 reflected = glm::reflect(glm::normalize(in.direction), rec.normal) + (Random::RandomInUnitSphere() * m_Roughness);

		if (glm::dot(reflected, rec.normal) < 0)
			return false;

		float fresnel = (glm::dot(in.direction, reflected) + 1) / 2.0f;
		fresnel = glm::pow(fresnel, 6.0f);

		scattered.direction = reflected;

		float ratio = m_Shininess;
		glm::vec3 mid = 
			(m_Specular * m_SpecularTint) +
			(glm::vec3(m_ShininessStrength *0.15f) * (1.f-m_SpecularTint));
		glm::vec3 outer = glm::vec3(m_ShininessStrength);
		glm::vec3 clearcoat = 
			(mid * (1 - fresnel)) +
			(outer * (fresnel));
		attenuation = (
			(m_Specular * (1-ratio)) +
			(clearcoat * (ratio))
		) / m_ShininessStrength;
		return true;
	}

	// Diffuse
	scattered.direction = rec.normal + Random::RandomUnitVector();
	if (almost_zero(scattered.direction))
		scattered.direction = rec.normal;
	scattered.direction = glm::normalize(scattered.direction);
	attenuation = m_Diffuse / (1 - m_ShininessStrength);

	return true;
}
