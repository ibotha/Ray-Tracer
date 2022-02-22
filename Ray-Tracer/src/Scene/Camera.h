#pragma once
#include <assimp/camera.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <string>
#include <Ray.h>

class Camera
{
public:
	Camera(const aiCamera* camera, aiNode * node);

	/*Generates a ray in world space using the scenes camera.
	the x and y are between -1 and 1 where -1 is left and bottom*/
	Ray GenerateRay(float x, float y) const;

	float FOV;
	float AR;
	float lens_radius;
	glm::mat4 view;
	glm::vec3 position;
	glm::vec3 lower_left_corner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
	glm::vec3 w;
	glm::vec3 u;
	glm::vec3 v;
	std::string name;
};

