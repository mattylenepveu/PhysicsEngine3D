#pragma once

// Include(s)
#include <glm\glm.hpp>
#include <glm\ext.hpp>

//--------------------------------------------------------------------------------
// Enum used to represent object types in the engine (they are unsigned ints so
// we allocate and use less memory).
//--------------------------------------------------------------------------------
enum ShapeType : unsigned short int
{
	PLANE = 0,
	SPHERE,			// SPHERE = 1
	BOX,			// BOX = 2
	SHAPE_COUNT		// SHAPE_COUNT = 3
};

// Acts as a Base Class
class PhysicsObject
{
protected:
	//--------------------------------------------------------------------------------
	// Default Constructor.
	//
	// Param:
	//		a_shapeID: An enum representing the number of the shape in the enum.
	//--------------------------------------------------------------------------------
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:
	//--------------------------------------------------------------------------------
	// Updates objects every frame (used in inherited classes).
	//--------------------------------------------------------------------------------
	virtual void fixedUpdate(glm::vec3 gravity, float timeStep) = 0;

	//--------------------------------------------------------------------------------
	// Function used for debugging purposes (used in inherited classes).
	//--------------------------------------------------------------------------------
	virtual void debug() = 0;

	//--------------------------------------------------------------------------------
	// Creates the Gizmos (used in inherited classes).
	//--------------------------------------------------------------------------------
	virtual void makeGizmo() = 0;

	//--------------------------------------------------------------------------------
	// A getter for the ShapeID that returns the ShapeID when called,
	//
	// Return:
	//		m_shapeID: Returns the number of the object in the enum.
	//--------------------------------------------------------------------------------
	ShapeType getShapeID() { return m_shapeID; }

protected:
	// ShapeType refers to the number of an object in the ShapeType enum
	ShapeType m_shapeID;
};

