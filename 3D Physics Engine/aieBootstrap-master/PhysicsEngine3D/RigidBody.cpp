#include "RigidBody.h"
static const float MIN_LINEAR_THRESHOLD = 0.02f;
static const float MIN_ROTATION_THRESHOLD = 0.02f;

RigidBody::RigidBody(ShapeType shapeID, glm::vec3 position, glm::vec3 velocity,
	float rotation, float mass, float linearDrag, float angularDrag,
	float elasticity) : PhysicsObject(shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
	m_linearDrag = linearDrag;
	m_angularDrag = angularDrag;
	m_elasticity = elasticity;
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec3 gravity, float timeStep)
{
	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;

	m_velocity -= m_velocity * m_linearDrag * timeStep;

	if (glm::length(m_velocity) < MIN_LINEAR_THRESHOLD)
	{
		m_velocity = glm::vec3(0, 0, 0);
	}
}

void RigidBody::applyForce(glm::vec3 force)
{
	m_velocity += force / m_mass;
}

void RigidBody::applyForceToActor(RigidBody* actor2, glm::vec3 force)
{
	actor2->applyForce(force);
	this->applyForce(-force);
}

void RigidBody::resolveCollision(RigidBody* actor2)
{
	glm::vec3 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec3 relativeVelocity = actor2->getVelocity() - m_velocity;

	float elasticity = (m_elasticity + actor2->getElasticity()) * 0.5f;

	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal)
		/ glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

	glm::vec3 force = normal * j;

	applyForceToActor(actor2, force);
}
