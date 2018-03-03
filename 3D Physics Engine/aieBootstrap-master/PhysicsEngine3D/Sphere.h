#pragma once

// Include(s)
#include "RigidBody.h"
#include <Gizmos.h>

// Class inherits from RigidBody class
class Sphere : public RigidBody
{
public:
	//--------------------------------------------------------------------------------
	// Default Constructor. (Deleted as we do not need it)
	//--------------------------------------------------------------------------------
	Sphere() = delete;

	//--------------------------------------------------------------------------------
	// Acts as an additional constructor.
	//
	// Param:
	//		position: A Vector3 that records the sphere's position in world space.
	//		velocity: A Vector3 that records the initial velocity of the sphere.
	//		mass: Represents the mass of the sphere as a float.
	//		radius: A float indicating the sphere's radius.
	//		colour: Indicates the colour of the sphere as a Vector4.
	//--------------------------------------------------------------------------------
	Sphere(glm::vec3 position, glm::vec3 velocity,
		   float mass, float radius, glm::vec4 colour);

	//--------------------------------------------------------------------------------
	// Default Destructor. (Not Being Used)
	//--------------------------------------------------------------------------------
	~Sphere() {}

	//--------------------------------------------------------------------------------
	// Function makes the Gizmo for the sphere.
	//--------------------------------------------------------------------------------
	virtual void makeGizmo()
	{
		// Calls the addSphere function to draw the sphere, passing in its contents
		aie::Gizmos::addSphere(m_position, m_radius, 12, 12, m_colour);
	}

	//--------------------------------------------------------------------------------
	// Resets the position and velocity of the box when called.
	//
	// Param:
	//		position: A Vector3 recording the boxes reset position in world space.
	//		velocity: A Vector3 that records the reset velocity of the box.
	//--------------------------------------------------------------------------------
	void resetPosition(glm::vec3 position, glm::vec3 velocity);

	//--------------------------------------------------------------------------------
	// A getter function that lets other classes get the colour of the sphere.
	//
	// Return:
	//		Returns the colour of the sphere as a Vector4.
	//--------------------------------------------------------------------------------
	glm::vec4 getColour() { return m_colour; }

	//--------------------------------------------------------------------------------
	// A getter function that lets other classes access the radius of the sphere.
	//
	// Return:
	//		Returns the radius of the sphere as a Vector3.
	//--------------------------------------------------------------------------------
	float getRadius() { return m_radius; }

protected:
	// A Vector4 representing the sphere's colour
	glm::vec4 m_colour;

	// Float used to indicate the radius of the sphere
	float m_radius;
};
