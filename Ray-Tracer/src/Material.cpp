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

float schlick(double cosine, double ref_idx) {
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool Dielectric::scatter(const Ray& in, const Intersection& i, glm::vec3& attenuation, Ray& scattered)
{
    attenuation = color;
    float etai_over_etat = i.outer_face ? (1.0 / ri) : ri;

    glm::vec3 unit_direction = glm::normalize(in.direction);
    float cos_theta = fmin(dot(-unit_direction, i.normal), 1.0);
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    if (etai_over_etat * sin_theta > 1.0) {
        glm::vec3 reflected = reflect(unit_direction, i.normal);
        scattered = Ray(i.location, reflected);
        return true;
    }
    float reflect_prob = schlick(cos_theta, etai_over_etat);
    if (random_double() < reflect_prob)
    {
        glm::vec3 reflected = reflect(unit_direction, i.normal);
        scattered = Ray(i.location, reflected);
        return true;
    }
    glm::vec3 refracted = refract(unit_direction, i.normal, etai_over_etat);
    scattered = Ray(i.location, refracted);
    return true;
}
