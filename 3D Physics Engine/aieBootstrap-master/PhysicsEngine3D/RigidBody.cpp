// Include(s)
#include "RigidBody.h"

// A const float indicating the minimum drag value
static const float MIN_LINEAR_THRESHOLD = 0.02f;

//--------------------------------------------------------------------------------
// Acts as an additional constructor.
//
// Param:
//		position: A Vector3 that records an object's position in world space.
//		velocity: A Vector3 that records the initial velocity of an object.
//		mass: Represents the mass of an object as a float.
//--------------------------------------------------------------------------------
RigidBody::RigidBody(ShapeType shapeID, glm::vec3 position, glm::vec3 velocity, 
					 float mass) : PhysicsObject(shapeID)
{
	// Sets values to be equal to the passed in values
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;

	// Initilizes floats for the drag and elasticity
	m_linearDrag = 1.0f;
	m_elasticity = 0.8f;
}

//--------------------------------------------------------------------------------
// Updates objects every frame (used in inherited classes).
//
// Param:
//		gravity: Represents the gravity as a Vector3.
//      timeStep: A float indicating the time step.
//--------------------------------------------------------------------------------
void RigidBody::fixedUpdate(glm::vec3 gravity, float timeStep)
{
	// Calculates the velocity using the gravity and the time step
	m_velocity += gravity * timeStep;

	// Calculates the position to apply to the object with the velocity
	m_position += m_velocity * timeStep;

	// Applies drag to the velocity
	m_velocity -= m_velocity * m_linearDrag * timeStep;

	// Checks if the length of the velocity vector is lower than the threshold
	if (glm::length(m_velocity) < MIN_LINEAR_THRESHOLD)
	{
		// Resets velocity of the RigidBody back to a zero Vector3
		m_velocity = glm::vec3(0, 0, 0);
	}
}

//--------------------------------------------------------------------------------
// Applies force to an object.
//
// Param:
//		force: A Vector3 used to represent the force on an object.
//--------------------------------------------------------------------------------
void RigidBody::applyForce(glm::vec3 force)
{
	// Applies the force to the velocity of the object
	m_velocity += force / m_mass;
}

//--------------------------------------------------------------------------------
// Applies force to an acting object after a collision.
//
// Param:
//		actor2: Represents the RigidBody of the other object.
//		force: A Vector3 used to represent the force of the collision.
//--------------------------------------------------------------------------------
void RigidBody::applyForceToActor(RigidBody* actor2, glm::vec3 force)
{
	// Applies the force to the second object
	actor2->applyForce(force);

	// Applies force to the current object this RigidBody is set to
	this->applyForce(-force);
}

//--------------------------------------------------------------------------------
// Resolves any collision that has occured between two objects.
//
// Param:
//		actor2: A RigidBody pointer indicating the colliding object.
//--------------------------------------------------------------------------------
void RigidBody::resolveCollision(RigidBody* actor2)
{
	// Normalises the vector between both object's positions
	glm::vec3 normal = glm::normalize(actor2->m_position - m_position);

	// Gets and stores the relative velocity between both objects in local Vector3
	glm::vec3 relativeVelocity = actor2->getVelocity() - m_velocity;

	// Calculates the average elasticity between the two objects
	float elasticity = (m_elasticity + actor2->getElasticity()) * 0.5f;

	// Calculates the j for use in the force equation
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal)
			/ glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

	// Calculates the force to apply to both objects
	glm::vec3 force = normal * j;

	// Applies the force to both of the objects
	applyForceToActor(actor2, force);
}
