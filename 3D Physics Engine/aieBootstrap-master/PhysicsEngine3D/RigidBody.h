#pragma once
#include "PhysicsObject.h"

class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType shapeID, glm::vec3 position, glm::vec3 velocity,
		float rotation, float mass, float linearDrag,
		float angularDrag, float elasticity);
	~RigidBody();

	virtual void fixedUpdate(glm::vec3 gravity, float timeStep);
	virtual void debug() {}

	void applyForce(glm::vec3 force);
	void applyForceToActor(RigidBody* actor2, glm::vec3 force);
	void resolveCollision(RigidBody* actor2);

	void setPosition(glm::vec3 pos) { m_position = pos; }
	glm::vec3 getPosition() { return m_position; }

	float getRotation() { return m_rotation; }
	float getMass() { return m_mass; }
	glm::vec3 getVelocity() { return m_velocity; }
	float getLinearDrag() { return m_linearDrag; }
	float getAngularDrag() { return m_angularDrag; }
	float getElasticity() { return m_elasticity; }

protected:
	glm::vec3 m_position;
	glm::vec3 m_velocity;

	float m_mass;
	float m_rotation;
	float m_angularVelocity;
	float m_linearDrag;
	float m_angularDrag;
	float m_elasticity;
};
