#include "Transform.h"

Transform::Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
{

	otw = glm::identity<glm::mat4>();
	otw *= glm::translate(pos);
	otw *= glm::rotate(rot.y, glm::vec3(0, 1, 0));
	otw *= glm::rotate(rot.z, glm::vec3(0, 0, 1));
	otw *= glm::rotate(rot.x, glm::vec3(1, 0, 0));
	otw *= glm::scale(scale);

	wto = glm::inverse(otw);
	wtoDir = {
		wto[0][0], wto[0][1], wto[0][2],
		wto[1][0], wto[1][1], wto[1][2],
		wto[2][0], wto[2][1], wto[2][2]
	};
	otwDir = {
		otw[0][0], otw[0][1], otw[0][2],
		otw[1][0], otw[1][1], otw[1][2],
		otw[2][0], otw[2][1], otw[2][2]
	};
	normalMat = glm::inverse(glm::transpose(otwDir));
}

Transform::Transform(const glm::mat4& base)
{
	otw = base;
	wto = glm::inverse(otw);
	wtoDir = {
		wto[0][0], wto[0][1], wto[0][2],
		wto[1][0], wto[1][1], wto[1][2],
		wto[2][0], wto[2][1], wto[2][2]
	};
	otwDir = {
		otw[0][0], otw[0][1], otw[0][2],
		otw[1][0], otw[1][1], otw[1][2],
		otw[2][0], otw[2][1], otw[2][2]
	};
	normalMat = glm::transpose(wtoDir);
}

Ray Transform::ToObjectSpace(const Ray& ray) const
{
	Ray ret(
		ToObjectSpace(ray.origin),
		ToObjectSpaceDir(ray.direction)
	);
	return ret;
}

Ray Transform::ToWorldSpace(const Ray& ray) const
{
	Ray ret(
		ToWorldSpace(ray.origin),
		ToWorldSpaceDir(ray.direction)
	);
	return ret;
}

glm::vec3 Transform::ToObjectSpaceDir(const glm::vec3& dir) const
{
	return wtoDir * dir;
}

glm::vec3 Transform::ToWorldSpaceDir(const glm::vec3& dir) const
{
	return otwDir * dir;
}

glm::vec3 Transform::ToWorldSpaceNormal(const glm::vec3& dir) const
{
	return normalMat * dir;
}

glm::vec3 Transform::ToObjectSpace(const glm::vec3& vec) const
{
	glm::vec4 temp = { vec.x, vec.y, vec.z, 1 };
	temp = wto * temp;
	return { temp.x, temp.y, temp.z };
}

glm::vec3 Transform::ToWorldSpace(const glm::vec3& vec) const
{
	glm::vec4 temp = { vec.x, vec.y, vec.z, 1 };
	temp = otw * temp;
	return { temp.x, temp.y, temp.z };
}
