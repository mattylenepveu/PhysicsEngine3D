#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"
#include <glm\glm.hpp>

class Plane : public PhysicsObject
{
public:
	Plane() = delete;
	Plane(glm::vec3 normal, float distance);
	~Plane();

	virtual void fixedUpdate(glm::vec3 gravity, float timeStep) {}
	virtual void debug() {}
	virtual void makeGizmo();
	virtual void resetPosition() {}

	void resolveCollision(RigidBody* actor2, glm::vec3 contact);

	glm::vec3 getNormal() { return m_normal; }
	float getDistance() { return m_distanceToOrigin; }

protected:
	glm::vec3 m_normal;

	float m_distanceToOrigin;
};
