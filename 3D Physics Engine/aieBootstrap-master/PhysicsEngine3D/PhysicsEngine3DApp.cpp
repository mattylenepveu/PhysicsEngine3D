#include "PhysicsEngine3DApp.h"
#include "Gizmos.h"
#include "Input.h"
#include "PhysicsScene.h"
#include "Box.h"
#include "Sphere.h"
#include "Plane.h"
#include "Imgui.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//--------------------------------------------------------------------------------
// Function acts as this class' constructor.
//
// Return:
//		Returns a bool indicating if function is called.
//--------------------------------------------------------------------------------
bool PhysicsEngine3DApp::startup() 
{
	// Sets background colour to a dark grey
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// Initializes gizmo primitive counts
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	// Creates simple camera transforms
	m_viewMatrix = glm::lookAt(glm::vec3(30), glm::vec3(0), glm::vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 
										  16.0f / 9.0f, 0.1f, 1000.0f);

	// Creates a "new" PhysicsScene pointer
	m_physicsScene = new PhysicsScene();

	// Sets gravity to -10 m/s/s on the Y axis
	m_physicsScene->setGravity(glm::vec3(0, -10, 0));

	// Initilizes time step to be 0.03
	m_physicsScene->setTimeStep(0.03f);

	// Sets values for the three boxes' positions
	m_box1pos = glm::vec3(10, 20, 1);
	m_box2pos = glm::vec3(-10, 20, 0);
	m_box3pos = glm::vec3(10, 20, 10);

	// Sets values for the three sphere's positions
	m_ball1pos = glm::vec3(10, 20, -9);
	m_ball2pos = glm::vec3(-10, 20, -9.5f);
	m_ball3pos = glm::vec3(-10, 20, 11);

	// Sets values for the three boxes' velocities
	m_box1vel = glm::vec3(-20, 0, 0);
	m_box2vel = glm::vec3(20, 0, 0);
	m_box3vel = glm::vec3(-20, 0, 0);

	// Sets values for the three sphere's velocities
	m_ball1vel = glm::vec3(-20, 0, 0);
	m_ball2vel = glm::vec3(20, 0, 0);
	m_ball3vel = glm::vec3(20, 0, 0);
	
	// Creates a "new" Box for the three boxes, each passing data in the parameters
	box1 = new Box(glm::vec3(m_box1pos), glm::vec3(m_box1vel), 
				   3.0f, 1.0f, 1.0f, 1.0f, glm::vec4(1, 0, 0, 1));
	box2 = new Box(glm::vec3(m_box2pos), glm::vec3(m_box2vel), 
				   3.0f, 1.0f, 1.0f, 1.0f, glm::vec4(0, 1, 0, 1));
	box3 = new Box(glm::vec3(m_box3pos), glm::vec3(m_box3vel), 
				   3.0f, 1.0f, 1.0f, 1.0f, glm::vec4(0, 0, 1, 1));

	// Creates a "new" sphere for the three spheres, each passing data in parameters
	ball1 = new Sphere(glm::vec3(m_ball1pos), glm::vec3(m_ball1vel), 
					   3.0f, 1.0f, glm::vec4(1, 1, 0, 1));
	ball2 = new Sphere(glm::vec3(m_ball2pos), glm::vec3(m_ball2vel), 
					   3.0f, 1.0f, glm::vec4(1, 0, 1, 1));
	ball3 = new Sphere(glm::vec3(m_ball3pos), glm::vec3(m_ball3vel), 
					   3.0f, 1.0f, glm::vec4(0, 1, 1, 1));

	// Creates a "new" plane, passing in the normal and distance of the plane
	Plane* plane = new Plane(glm::normalize(glm::vec3(0, 1, 0)), 0);

	// Adds all three boxes as actors to the physics scene
	m_physicsScene->addActor(box1);
	m_physicsScene->addActor(box2);
	m_physicsScene->addActor(box3);

	// Adds all three boxes as actors to the physics scene
	m_physicsScene->addActor(ball1);
	m_physicsScene->addActor(ball2);
	m_physicsScene->addActor(ball3);

	// Adds the plane to the physics scene as an actor
	m_physicsScene->addActor(plane);

	// Returns true by default
	return true;
}

//--------------------------------------------------------------------------------
// Function acts as this class' destructor.
//--------------------------------------------------------------------------------
void PhysicsEngine3DApp::shutdown() 
{
	// Deletes all the created Gizmos
	aie::Gizmos::destroy();

	// Deletes the physics scene pointer
	delete m_physicsScene;
}

//--------------------------------------------------------------------------------
// Updates all the variables every frame.
//
// Param:
//		deltaTime: A float used to indicate real time.
//--------------------------------------------------------------------------------
void PhysicsEngine3DApp::update(float deltaTime) 
{
	ImGui::Begin("Add Box");

	if (ImGui::Button("Add Box", ImVec2(50, 50)))
	{
		Box* newBox = new Box(glm::vec3(0, 10, 0), glm::vec3(2, 0, 0),
							  3.0f, 1.0f, 1.0f, 1.0f, glm::vec4(1, 0, 0, 1));
		m_physicsScene->addActor(newBox);
	}

	ImGui::End();

	//glClear(GL_COLOR_BUFFER_BIT);

	////tetgui();

	////collisionDebugInfo();

	//ImGui::End();

	// Query time since application started
	float time = getTime();

	// Wipe the gizmos clean for this frame
	aie::Gizmos::clear();

	// Initilizes black as a colour for use when lines are drawn
	glm::vec4 black(0, 0, 0, 1);

	// Draws a simple grid with gizmos
	for (int i = 0; i < 41; ++i)
	{
		aie::Gizmos::addLine(glm::vec3(-20 + i, 0, 20),
						glm::vec3(-20 + i, 0, -20),
						black);
		aie::Gizmos::addLine(glm::vec3(20, 0, -20 + i),
						glm::vec3(-20, 0, -20 + i),
						black);
	}

	// Updates the Physics Scene every frame
	m_physicsScene->update(deltaTime);

	// Updates the gizmos that are apart of the Physics Scene
	m_physicsScene->updateGizmos();

	// Add a transform so that we can see the axis
	aie::Gizmos::addTransform(glm::mat4(1));
	
	// Creates a local input pointer so user can move the camera
	aie::Input* input = aie::Input::getInstance();

	// Checks if the "R" key has been pressed
	if (input->wasKeyPressed(aie::INPUT_KEY_R))
	{
		// Calls resetPosition function for the boxes
		box1->resetPosition(m_box1pos, m_box1vel);
		box2->resetPosition(m_box2pos, m_box2vel);
		box3->resetPosition(m_box3pos, m_box3vel);

		// Calls resetPosition function for the spheres
		ball1->resetPosition(m_ball1pos, m_ball1vel);
		ball2->resetPosition(m_ball2pos, m_ball2vel);
		ball3->resetPosition(m_ball3pos, m_ball3vel);
	}

	// Checks if the "UP" key is down every frame
	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		// Creates a world matrix as an inverse of the view matrix
		glm::mat4 worldMatrix = inverse(m_viewMatrix);

		// Sets the position of the camera and zooms it out
		worldMatrix[3] -= worldMatrix[2] * deltaTime * 10.0f;

		// Updates the view matrix
		m_viewMatrix = inverse(worldMatrix);
	}

	// Checks if the "DOWN" key is down every frame
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		// Creates a world matrix as an inverse of the view matrix
		glm::mat4 worldMatrix = inverse(m_viewMatrix);

		// Sets the position of the camera and zooms it in
		worldMatrix[3] += worldMatrix[2] * deltaTime * 10.0f;

		// Updates the view matrix
		m_viewMatrix = inverse(worldMatrix);
	}

	// Checks if the "LEFT" key is down every frame
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		// Creates a world matrix as an inverse of the view matrix
		glm::mat4 worldMatrix = inverse(m_viewMatrix);

		// Creates a rotation matrix, allowing user to rotate camera left
		glm::mat4 rot = glm::rotate(glm::mat4(1.0f), deltaTime * -1.0f, 
									glm::vec3(m_viewMatrix * glm::vec4(0, 1, 0, 0)));

		// Multiplies world matrix by the rotation matrix
		worldMatrix *= rot;

		// Updates the view matrix
		m_viewMatrix = inverse(worldMatrix);
	}

	// Checks if the "RIGHT" key is down every frame
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		// Creates a world matrix as an inverse of the view matrix
		glm::mat4 worldMatrix = inverse(m_viewMatrix);

		// Creates a rotation matrix, allowing user to rotate camera right
		glm::mat4 rot = glm::rotate(glm::mat4(1.0f), deltaTime * 1.0f, 
									glm::vec3(m_viewMatrix * glm::vec4(0, 1, 0, 0)));

		// Multiplies world matrix by the rotation matrix
		worldMatrix *= rot;

		// Updates the view matrix
		m_viewMatrix = inverse(worldMatrix);
	}

	// Close application if we press "ESCAPE"
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

//--------------------------------------------------------------------------------
// Draws all the Gizmos into the application when called.
//--------------------------------------------------------------------------------
void PhysicsEngine3DApp::draw() 
{
	// Wipes the screen to the background colour
	clearScreen();

	// Updates perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / 
										 (float)getWindowHeight(), 0.1f, 1000.0f);

	// Draws the gizmos based on the projection matrix times the view matrix
	aie::Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}