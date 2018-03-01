#pragma once

// Include(s)
#include "Application.h"
#include <glm/mat4x4.hpp>

// Forward Declare(s)
class PhysicsScene;
class Box;
class Sphere;

// Class inherits from Application in bootstrap
class PhysicsEngine3DApp : public aie::Application 
{
public:
	//--------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------
	PhysicsEngine3DApp() {}

	//--------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------
	virtual ~PhysicsEngine3DApp() {}

	//--------------------------------------------------------------------------------
	// Function acts as this class' constructor.
	//
	// Return:
	//		Returns a bool indicating if function is called.
	//--------------------------------------------------------------------------------
	virtual bool startup();

	//--------------------------------------------------------------------------------
	// Function acts as this class' destructor.
	//--------------------------------------------------------------------------------
	virtual void shutdown();

	//--------------------------------------------------------------------------------
	// Updates all the variables every frame.
	//
	// Param:
	//		deltaTime: A float used to indicate real time.
	//--------------------------------------------------------------------------------
	virtual void update(float deltaTime);

	//--------------------------------------------------------------------------------
	// Draws all the Gizmos into the application when called.
	//--------------------------------------------------------------------------------
	virtual void draw();

protected:
	// Matrix4s used for camera transforms
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	// PhysicsScene pointer used for indicating a PhysicsScene
	PhysicsScene* m_physicsScene;

	// Box pointers used to create three new boxes
	Box* box1;
	Box* box2;
	Box* box3;

	// Sphere pointers used to create three new spheres
	Sphere* ball1;
	Sphere* ball2;
	Sphere* ball3;

	// Vector3s used to initilize the three boxes' positions
	glm::vec3 m_box1pos;
	glm::vec3 m_box2pos;
	glm::vec3 m_box3pos;

	// Vector3s used to initilize the three sphere's positions
	glm::vec3 m_ball1pos;
	glm::vec3 m_ball2pos;
	glm::vec3 m_ball3pos;

	// Vector3s used to initilize the three boxes' velocities
	glm::vec3 m_box1vel;
	glm::vec3 m_box2vel;
	glm::vec3 m_box3vel;

	// Vector3s used to initilize the three sphere's velocities
	glm::vec3 m_ball1vel;
	glm::vec3 m_ball2vel;
	glm::vec3 m_ball3vel;
};