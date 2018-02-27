#include "RigidBody.h"
static const float MIN_LINEAR_THRESHOLD = 0.02f;
static const float MIN_ROTATION_THRESHOLD = 0.02f;

RigidBody::RigidBody(ShapeType shapeID, glm::vec3 position, glm::vec3 velocity, float mass) : PhysicsObject(shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;

	m_linearDrag = 1.0f;
	m_angularDrag = 1.0f;
	m_elasticity = 0.8f;
	m_angularVelocity = glm::vec3(0.1f);

	m_rotation = glm::mat4(1);
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec3 gravity, float timeStep)
{
	glm::quat xRotation = glm::angleAxis(m_angularVelocity.x * timeStep, glm::vec3(1, 0, 0));
	glm::quat yRotation = glm::angleAxis(m_angularVelocity.y * timeStep, glm::vec3(0, 1, 0));
	glm::quat zRotation = glm::angleAxis(m_angularVelocity.z * timeStep, glm::vec3(0, 0, 1));

	glm::quat rotation = xRotation * yRotation * zRotation;
	m_rotation = glm::mat4_cast(rotation) * m_rotation;

	m_velocity += gravity * timeStep;
	m_position += m_velocity * timeStep;
	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= glm::cross(m_angularVelocity, m_position) * m_angularDrag * timeStep;

	if (glm::length(m_velocity) < MIN_LINEAR_THRESHOLD)
	{
		m_velocity = glm::vec3(0, 0, 0);
	}

	if (glm::length(m_angularVelocity) < MIN_ROTATION_THRESHOLD)
	{
		m_angularVelocity = glm::vec3(0, 0, 0);
	}
}

void RigidBody::applyForce(glm::vec3 force, glm::vec3 pos)
{
	m_velocity += force / m_mass;
	m_angularVelocity += glm::cross(force, pos) / (m_moment);
}

//void RigidBody::applyForceToActor(RigidBody* actor2, glm::vec3 force)
//{
//	actor2->applyForce(force);
//	this->applyForce(-force);
//}

void RigidBody::resolveCollision(RigidBody* actor2, glm::vec3 contact, glm::vec3* collisionNormal)
{
	glm::vec3 normal = collisionNormal ? *collisionNormal :	
					   glm::normalize(actor2->m_position - m_position);
	//glm::vec3 relativeVelocity = actor2->getVelocity() - m_velocity;

	glm::vec3 perp(normal.y, -normal.x, normal.z);

	float r1 = glm::dot(contact - m_position, -perp);
	float r2 = glm::dot(contact - actor2->m_position, perp);
	glm::vec3 v1 = glm::dot(m_velocity, normal) - r1 * m_angularVelocity;
	glm::vec3 v2 = glm::dot(actor2->m_velocity, normal) + r2 * actor2->m_angularVelocity;

	if (glm::length(v1) > glm::length(v2))
	{
		float mass1 = 1.0f / (1.0f / m_mass + (r1 * r1) / m_moment);
		float mass2 = 1.0f / (1.0f / actor2->m_mass + (r2 * r2) / actor2->m_moment);

		float elasticity = (m_elasticity + actor2->getElasticity()) * 0.5f;

		glm::vec3 force = (1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2) * normal;

		applyForce(-force, contact - m_position);
		actor2->applyForce(force, contact - actor2->m_position);
	}

	/*float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal)
		/ glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));*/

	//applyForceToActor(actor2, force);
}
