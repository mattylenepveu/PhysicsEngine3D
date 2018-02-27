#pragma once
#include "RigidBody.h"

class Sphere : public RigidBody
{
public:
	Sphere() = delete;
	Sphere(glm::vec3 position, glm::vec3 velocity,
		float mass, float radius, glm::vec4 colour);
	~Sphere();

	virtual void makeGizmo();
	void resetPosition(glm::vec3 position, glm::vec3 velocity);

	float getRadius() { return m_radius; }
	glm::vec4 getColour() { return m_colour; }

protected:
	float m_radius;
	glm::vec4 m_colour;
};
