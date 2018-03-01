#pragma once

// Include(s)
#include "RigidBody.h"
#include <Gizmos.h>

// Class inherits from RigidBody class
class Box : public RigidBody
{
public:
	//--------------------------------------------------------------------------------
	// Default Constructor. (Deleted as we do not need it)
	//--------------------------------------------------------------------------------
	Box() = delete;

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
	Box(glm::vec3 position, glm::vec3 velocity, float mass,
		float width, float height, float depth, glm::vec4 colour);

	//--------------------------------------------------------------------------------
	// Default Destructor. (Not Being Used)
	//--------------------------------------------------------------------------------
	~Box() {}

	//--------------------------------------------------------------------------------
	// Updates the boxes' variables and is called every frame.
	//
	// Param:
	//		gravity: Represents the gravity as a Vector3.
	//		timeStep: A float indicating the time step.
	//--------------------------------------------------------------------------------
	void fixedUpdate(glm::vec3 gravity, float timeStep)
	{
		RigidBody::fixedUpdate(gravity, timeStep);
	}

	//--------------------------------------------------------------------------------
	// Function makes the Gizmo for the box.
	//--------------------------------------------------------------------------------
	virtual void makeGizmo()
	{
		// Calls addAABBFilled function passing in boxes' position, dimensions and colour
		aie::Gizmos::addAABBFilled(m_position, m_dimensions, m_colour);
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
	// A getter function that returns the width of the box.
	//
	// Return:
	//		Returns the boxes' width as a float.
	//--------------------------------------------------------------------------------
	float getWidth() { return m_width; }

	//--------------------------------------------------------------------------------
	// A getter function that returns the height of the box.
	//
	// Return:
	//		Returns the boxes' height as a float.
	//--------------------------------------------------------------------------------
	float getHeight() { return m_height; }

	//--------------------------------------------------------------------------------
	// A getter function that returns the depth of the box.
	//
	// Return:
	//		Returns the boxes' depth as a float.
	//--------------------------------------------------------------------------------
	float getDepth() { return m_depth; }

	//--------------------------------------------------------------------------------
	// A getter function that returns the dimensions of the box.
	//
	// Return:
	//		Returns the boxes' dimensions as a Vector3.
	//--------------------------------------------------------------------------------
	glm::vec3 getDimensions() { return m_dimensions; }

	//--------------------------------------------------------------------------------
	// A getter function that returns the minimum Vector3 of the box.
	//
	// Return:
	//		Returns the boxes' minimum Vector3.
	//--------------------------------------------------------------------------------
	glm::vec3 getMin() 
	{
		return glm::vec3(m_position.x - m_width, m_position.y - m_height, 
						 m_position.z - m_depth);
	}

	//--------------------------------------------------------------------------------
	// A getter function that returns the maximum Vector3 of the box.
	//
	// Return:
	//		Returns the boxes' maximum Vector3.
	//--------------------------------------------------------------------------------
	glm::vec3 getMax() 
	{
		return glm::vec3(m_position.x + m_width, m_position.y + m_height, 
						 m_position.z + m_depth);
	}

	//--------------------------------------------------------------------------------
	// A getter function that returns the colour of the box.
	//
	// Return:
	//		Returns the boxes' colour as a Vector4.
	//--------------------------------------------------------------------------------
	glm::vec4 getColour() { return m_colour; }

protected:
	// Floats used to represent the width, height and depth of the box
	float m_width;
	float m_height;
	float m_depth;

	// Vector3 used to represent the dimensions of the box
	glm::vec3 m_dimensions;

	// Vector4 used to represent the colour of the box
	glm::vec4 m_colour;
};

