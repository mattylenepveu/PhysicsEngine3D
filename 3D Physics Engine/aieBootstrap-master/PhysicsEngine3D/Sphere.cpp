// Include(s)
#include "Sphere.h"

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
Sphere::Sphere(glm::vec3 position, glm::vec3 velocity,
			   float mass, float radius, glm::vec4 colour) :
			   RigidBody(ShapeType::SPHERE, position, velocity, mass)
{
	// Sets radius and colour to equal the passed in values
	m_radius = radius;
	m_colour = colour;

	// Calculates the moment of the sphere
	m_moment = 0.5f * mass * radius * radius;
}

//--------------------------------------------------------------------------------
// Resets the position and velocity of the box when called.
//
// Param:
//		position: A Vector3 recording the boxes reset position in world space.
//		velocity: A Vector3 that records the reset velocity of the box.
//--------------------------------------------------------------------------------
void Sphere::resetPosition(glm::vec3 position, glm::vec3 velocity)
{
	// Sets the position and velocity of the sphere to equal passed in values
	m_position = position;
	m_velocity = velocity;
}
