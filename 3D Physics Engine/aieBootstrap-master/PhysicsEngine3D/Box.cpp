// Include(s)
#include "Box.h"

//--------------------------------------------------------------------------------
// Acts as an additional constructor.
//
// Param:
//		position: A Vector3 that records the boxes position in world space.
//		velocity: A Vector3 that records the initial velocity of the box.
//		mass: Represents the mass of the box as a float.
//		width: A float initializing the boxes' width.
//		height: A float initializing the boxes' height.
//		depth: A float initializing the boxes' depth.
//		colour: Indicates the colour of the box as a Vector4.
//--------------------------------------------------------------------------------
Box::Box(glm::vec3 position, glm::vec3 velocity, float mass,
	float width, float height, float depth, glm::vec4 colour) :
	RigidBody(ShapeType::BOX, position, velocity, mass)
{
	// Initilizing variables to equal the values being passed in
	m_width = width;
	m_height = height;
	m_depth = depth;
	m_colour = colour;

	// Sets the dimensions to equal a Vector3 with width, height and depth passed in
	m_dimensions = glm::vec3(m_width, m_height, m_depth);

	// Initilizes moment to equal math equation with boxes' dimensions
	m_moment = 1.0f / 12.0f * mass * width * height;
}

//--------------------------------------------------------------------------------
// Resets the position and velocity of the box when called.
//
// Param:
//		position: A Vector3 recording the boxes reset position in world space.
//		velocity: A Vector3 that records the reset velocity of the box.
//--------------------------------------------------------------------------------
void Box::resetPosition(glm::vec3 position, glm::vec3 velocity)
{
	// Initilizing variables to equal the values being passed in
	m_position = position;
	m_velocity = velocity;
}
