#pragma once

// Include(s)
#include "PhysicsObject.h"
#include "RigidBody.h"
#include <glm\glm.hpp>

// Class inherits from PhysicsObject class
class Plane : public PhysicsObject
{
public:
	//--------------------------------------------------------------------------------
	// Default Constructor. (Deleted as we do not need it)
	//--------------------------------------------------------------------------------
	Plane() = delete;

	//--------------------------------------------------------------------------------
	// Acts as an additional constructor.
	//
	// Param:
	//		normal: A Vector3 that records the normal of the plane
	//		velocity: A float that records the distance of the plane
	//--------------------------------------------------------------------------------
	Plane(glm::vec3 normal, float distance);

	//--------------------------------------------------------------------------------
	// Default Destructor. (Not Being Used)
	//--------------------------------------------------------------------------------
	~Plane() {}

	//--------------------------------------------------------------------------------
	// Updates the plane's variables and is called every frame. (Not being used)
	//
	// Param:
	//		gravity: Represents the gravity as a Vector3.
	//		timeStep: A float indicating the time step.
	//--------------------------------------------------------------------------------
	virtual void fixedUpdate(glm::vec3 gravity, float timeStep) {}

	//--------------------------------------------------------------------------------
	// Function makes the Gizmo for the plane.
	//--------------------------------------------------------------------------------
	virtual void makeGizmo();

	//--------------------------------------------------------------------------------
	// Resolves any collision that has occured between the plane and another object.
	//
	// Param:
	//		actor2: A RigidBody pointer indicating the colliding object
	//		contact: A Vector3 that indicates how much contact has been made
	//--------------------------------------------------------------------------------
	void resolveCollision(RigidBody* actor2, glm::vec3 contact);

	glm::vec3 getNormal() { return m_normal; }
	float getDistance() { return m_distanceToOrigin; }

protected:
	glm::vec3 m_normal;

	float m_distanceToOrigin;
};
