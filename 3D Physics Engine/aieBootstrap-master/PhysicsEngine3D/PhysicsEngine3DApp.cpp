#include "PhysicsEngine3DApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Box.h"
#include "Sphere.h"
#include "Plane.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

PhysicsEngine3DApp::PhysicsEngine3DApp() {

}

PhysicsEngine3DApp::~PhysicsEngine3DApp() {

}

bool PhysicsEngine3DApp::startup() 
{
	setBackgroundColour(1, 1, 1);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(30), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(vec3(0, -10, 0));
	m_physicsScene->setTimeStep(0.03f);

	Box* box1 = new Box(vec3(-10, 15, 0), vec3(20, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, vec4(1, 0, 0, 1));
	Box* box2 = new Box(vec3(-8, 15, 5), vec3(16, 0, 1), 3.0f, 1.0f, 1.0f, 1.0f, vec4(0, 1, 0, 1));
	Sphere* ball1 = new Sphere(vec3(5, 15, 1), vec3(12, 0, 0), 3.0f, 1.0f, vec4(0, 0, 1, 1));
	Sphere* ball2 = new Sphere(vec3(10, 15, -3), vec3(-20, 0, 2), 3.0f, 1.0f, vec4(1, 1, 0, 1));

	/*wall1 = new Box(vec3(0, 0, 0), vec3(0, 0, 0), 3.0f, 15.0f, 15.0f, 0.5f, vec4(1, 1, 1, 0.8f));
	wall2 = new Box(vec3(-8, 15, 5), vec3(0, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, vec4(1, 1, 1, 0.5f));
	wall3 = new Box(vec3(-10, 15, 0), vec3(0, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, vec4(1, 1, 1, 0.5f));
	wall4 = new Box(vec3(-8, 15, 5), vec3(0, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, vec4(1, 1, 1, 0.5f));
	wall5 = new Box(vec3(-10, 15, 0), vec3(0, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, vec4(1, 1, 1, 0.5f));*/

	/*box1->applyForce(vec3(20, 0, 0));
	box2->applyForce(vec3(16, 0, 1));
	ball1->applyForce(vec3(12, 0, 0));
	ball2->applyForce(vec3(-20, 0, 2));*/

	m_physicsScene->addActor(box1);
	m_physicsScene->addActor(box2);
	m_physicsScene->addActor(ball1);
	m_physicsScene->addActor(ball2);

	return true;
}

void PhysicsEngine3DApp::shutdown() 
{
	Gizmos::destroy();
	delete m_physicsScene;

	/*delete wall1;
	delete wall2;
	delete wall3;
	delete wall4;
	delete wall5;*/
}

void PhysicsEngine3DApp::update(float deltaTime) 
{
	// query time since application started
	float time = getTime();

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 31; ++i) \
	{
		Gizmos::addLine(vec3(-15 + i, 0, 15),
						vec3(-15 + i, 0, -15),
						black);
		Gizmos::addLine(vec3(15, 0, -15 + i),
						vec3(-15, 0, -15 + i),
						black);

		Gizmos::addLine(vec3(-15, i, 15),
						vec3(-15, i, -15),
						black);
		Gizmos::addLine(vec3(-15, 30, -15 + i),
						vec3(-15, 0, -15 + i),
						black);

		Gizmos::addLine(vec3(15, i, -15),
						vec3(-15, i, -15),
						black);
		Gizmos::addLine(vec3(-15 + i, 30, -15),
						vec3(-15 + i, 0, -15),
						black);

		Gizmos::addLine(vec3(15, i, 15),
						vec3(15, i, -15),
						black);
		Gizmos::addLine(vec3(15, 30, -15 + i),
						vec3(15, 0, -15 + i),
						black);

		Gizmos::addLine(vec3(15, i, 15),
						vec3(-15, i, 15),
						black);
		Gizmos::addLine(vec3(-15 + i, 30, 15),
						vec3(-15 + i, 0, 15),
						black);
	}

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));
	
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		mat4 worldMatrix = inverse(m_viewMatrix);
		worldMatrix[3] -= worldMatrix[2] * deltaTime * 10.0f;
		m_viewMatrix = inverse(worldMatrix);
	}

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		mat4 worldMatrix = inverse(m_viewMatrix);
		worldMatrix[3] += worldMatrix[2] * deltaTime * 10.0f;
		m_viewMatrix = inverse(worldMatrix);
	}

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		mat4 worldMatrix = inverse(m_viewMatrix);

		mat4 rot = glm::rotate(mat4(1.0f), deltaTime * -1.0f, vec3(m_viewMatrix * vec4(0, 1, 0, 0)));
			//vec3(worldMatrix[1]));
		
		//worldMatrix = rot * worldMatrix;
		worldMatrix = worldMatrix * rot;

		m_viewMatrix = inverse(worldMatrix);
	}

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		mat4 worldMatrix = inverse(m_viewMatrix);

		mat4 rot = glm::rotate(mat4(1.0f), deltaTime * +1.0f, vec3(m_viewMatrix * vec4(0, 1, 0, 0)));
		//vec3(worldMatrix[1]));

		//worldMatrix = rot * worldMatrix;
		worldMatrix = worldMatrix * rot;

		m_viewMatrix = inverse(worldMatrix);
	}


	// quit if we press escape
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsEngine3DApp::draw() 
{
	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}