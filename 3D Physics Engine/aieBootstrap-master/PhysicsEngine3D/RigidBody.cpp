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
	m_velocity += gravity * timeStep;
	m_position += m_velocity * timeStep;

	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_rotation += m_angularVelocity * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;

	if (glm::length(m_velocity) < MIN_LINEAR_THRESHOLD)
	{
		m_velocity = glm::vec3(0, 0, 0);
	}

	if (abs(m_angularVelocity) < MIN_ROTATION_THRESHOLD)
	{
		m_angularVelocity = 0;
	}
}

void RigidBody::applyForce(glm::vec3 force, glm::vec3 pos)
{
	m_velocity += force / m_mass;
	m_angularVelocity += (force.x * pos.y -
						  force.x * pos.z -
						  force.y * pos.x -
						  force.y * pos.z -
						  force.z * pos.x -
						  force.z * pos.y)
						  / (m_moment);
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
	float v1 = glm::dot(m_velocity, normal) - r1 * m_rotation;
	float v2 = glm::dot(actor2->m_velocity, normal) + r2 * m_rotation;

	if (v1 > v2)
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
