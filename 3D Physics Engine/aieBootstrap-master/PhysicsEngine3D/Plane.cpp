// Include(s)
#include "Plane.h"
#include "PhysicsObject.h"
#include "Gizmos.h"
#include <glm\ext.hpp>

//--------------------------------------------------------------------------------
// Acts as an additional constructor.
//
// Param:
//		normal: A Vector3 that records the normal of the plane
//		velocity: A float that records the distance of the plane
//--------------------------------------------------------------------------------
Plane::Plane(glm::vec3 normal, float distance) : PhysicsObject(ShapeType::PLANE)
{
	// Sets the distance and normal to the passed in values
	m_distanceToOrigin = distance;
	m_normal = normal;
}

//--------------------------------------------------------------------------------
// Resolves any collision that has occured between the plane and another object.
//
// Param:
//		actor2: A RigidBody pointer indicating the colliding object
//--------------------------------------------------------------------------------
void Plane::resolveCollision(RigidBody* actor2/*, glm::vec3 contact*/)
{
	// Gets the velocity of the other object and stores in local Vector3
	glm::vec3 vRel = actor2->getVelocity();

	// Gets the elasticity of the other object and stores in local float
	float e = actor2->getElasticity();

	// Calculates the j for use in force equation
	float j = glm::dot(-(1 + e) * (vRel), m_normal) / (1 / actor2->getMass());

	// Calculates the force to apply to the other object
	glm::vec3 force = m_normal * j;

	// Applies the force to the object
	actor2->applyForce(force);
}
