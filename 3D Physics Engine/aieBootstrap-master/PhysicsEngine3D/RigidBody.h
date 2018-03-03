#pragma once

// Include(s)
#include "PhysicsObject.h"

// Class inherits from PhysicsObject class
class RigidBody : public PhysicsObject
{
public:
	//--------------------------------------------------------------------------------
	// Default Constructor. (Deleted as we do not need it)
	//--------------------------------------------------------------------------------
	RigidBody() = delete;

	//--------------------------------------------------------------------------------
	// Acts as an additional constructor.
	//
	// Param:
	//		position: A Vector3 that records an object's position in world space.
	//		velocity: A Vector3 that records the initial velocity of an object.
	//		mass: Represents the mass of an object as a float.
	//--------------------------------------------------------------------------------
	RigidBody(ShapeType shapeID, glm::vec3 position, glm::vec3 velocity, float mass);

	//--------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------
	~RigidBody() {}

	//--------------------------------------------------------------------------------
	// Updates objects every frame (used in inherited classes).
	//
	// Param:
	//		gravity: Represents the gravity as a Vector3.
	//      timeStep: A float indicating the time step.
	//--------------------------------------------------------------------------------
	virtual void fixedUpdate(glm::vec3 gravity, float timeStep);

	//--------------------------------------------------------------------------------
	// Function used for debugging purposes (used in inherited classes).
	//--------------------------------------------------------------------------------
	virtual void debug() {}

	//--------------------------------------------------------------------------------
	// Applies force to an object.
	//
	// Param:
	//		force: A Vector3 used to represent the force on an object.
	//--------------------------------------------------------------------------------
	void applyForce(glm::vec3 force);

	//--------------------------------------------------------------------------------
	// Applies force to an acting object after a collision.
	//
	// Param:
	//		actor2: Represents the RigidBody of the other object.
	//		force: A Vector3 used to represent the force of the collision.
	//--------------------------------------------------------------------------------
	void applyForceToActor(RigidBody* actor2, glm::vec3 force);

	//--------------------------------------------------------------------------------
	// Resolves any collision that has occured between two objects.
	//
	// Param:
	//		actor2: A RigidBody pointer indicating the colliding object.
	//--------------------------------------------------------------------------------
	void resolveCollision(RigidBody* actor2);

	//--------------------------------------------------------------------------------
	// A setter function that lets other classes set the position of an object.
	//
	// Param:
	//		pos: A Vector3 indicating the position the object will be set to.
	//--------------------------------------------------------------------------------
	void setPosition(glm::vec3 pos) { m_position = pos; }

	//--------------------------------------------------------------------------------
	// A getter function that lets other classes get the position of an object.
	//
	// Return:
	//		Returns the position of an object as a Vector3.
	//--------------------------------------------------------------------------------
	glm::vec3 getPosition() { return m_position; }

	//--------------------------------------------------------------------------------
	// A getter function that lets other classes get the velocity of an object.
	//
	// Return:
	//		Returns the velocity of an object as a Vector3.
	//--------------------------------------------------------------------------------
	glm::vec3 getVelocity() { return m_velocity; }

	//--------------------------------------------------------------------------------
	// A getter function that lets other classes access the mass of an object.
	//
	// Return:
	//		Returns the mass of an object as a float.
	//--------------------------------------------------------------------------------
	float getMass() { return m_mass; }

	//--------------------------------------------------------------------------------
	// A getter function that lets other classes get the elasticity of an object.
	//
	// Return:
	//		Returns the elasticity of an object as a float.
	//--------------------------------------------------------------------------------
	float getElasticity() { return m_elasticity; }

protected:
	// Vector3's represent the position and velocity of the RigidBody
	glm::vec3 m_position;
	glm::vec3 m_velocity;

	// Floats used to represent mass, moment, drag and elasticity of an object
	float m_mass;
	float m_moment;
	float m_linearDrag;
	float m_elasticity;
};
