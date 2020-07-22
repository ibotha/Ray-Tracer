#include "Material.h"
#include "Random.h"

Diffuse::Diffuse(const glm::vec3& _diffuseColour, float _roughness)
	:diffuseColor(_diffuseColour), roughness(_roughness)
{
}

bool Diffuse::scatter(const Ray& in, const Intersection& intersection, glm::vec3& attenuation, Ray& scattered)
{
    glm::vec3 scatter_direction = intersection.normal + random_unit_vector();
    scattered = Ray(intersection.location, scatter_direction);
    attenuation = diffuseColor;
    return true;
}

Metal::Metal(const glm::vec3& _color, float _roughness)
    :color(_color), roughness(_roughness)
{
}

bool Metal::scatter(const Ray& in, const Intersection& intersection, glm::vec3& attenuation, Ray& scattered)
{
    glm::vec3 reflected = glm::reflect(in.direction, intersection.normal);
    scattered = Ray(intersection.location, reflected + random_unit_vector() * roughness);
    attenuation = color;
    return (glm::dot(scattered.direction, intersection.normal) > 0);
}

Dielectric::Dielectric(const glm::vec3& _color, float _roughness, float _ri)
    :color(_color), roughness(_roughness), ri(_ri)
{
}

bool Dielectric::scatter(const Ray& in, const Intersection& intersection, glm::vec3& attenuation, Ray& scattered)
{
    attenuation = color;
    float etai_over_etat = intersection.inner_face ? ri : (1.0f / ri);
    float cos_theta = glm::min(glm::dot(-in.direction, intersection.normal), 1.0f);
    float sin_theta = glm::sqrt(1.0f - cos_theta * cos_theta);
    if (etai_over_etat * sin_theta > 1.0f) {
        glm::vec3 reflected = reflect(in.direction, intersection.normal);
        scattered = Ray(intersection.location, reflected + random_unit_vector() * roughness);
        return true;
    }

    auto r0 = (1 - etai_over_etat) / (1 + etai_over_etat);
    r0 = r0 * r0;
    float reflect_prob = r0 + (1 - r0) * pow((1 - cos_theta), 5);
    if (random_double() < reflect_prob)
    {
        glm::vec3 reflected = reflect(in.direction, intersection.normal);
        scattered = Ray(intersection.location, reflected + random_unit_vector() * roughness);
        return true;
    }
    glm::vec3 refracted = glm::refract(in.direction, intersection.normal, etai_over_etat);
    scattered = Ray(intersection.location, refracted + random_unit_vector() * roughness);
    return true;
}
