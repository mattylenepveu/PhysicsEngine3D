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
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(30), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(vec3(0, -10, 0));
	m_physicsScene->setTimeStep(0.03f);

	m_box1pos = vec3(10, 20, 0);
	m_box2pos = vec3(-10, 20, 0);
	m_box3pos = vec3(10, 20, 10);

	m_ball1pos = vec3(10, 20, -10);
	m_ball2pos = vec3(-10, 20, -10);
	m_ball3pos = vec3(-10, 20, 10);

	m_box1vel = vec3(-20, 0, 0);
	m_box2vel = vec3(20, 0, 0);
	m_box3vel = vec3(-20, 0, 0);

	m_ball1vel = vec3(-20, 0, 0);
	m_ball2vel = vec3(20, 0, 0);
	m_ball3vel = vec3(20, 0, 0);

	box1 = new Box(vec3(m_box1pos), vec3(m_box1vel), 3.0f, 1.0f, 1.0f, 1.0f, vec4(1, 0, 0, 1));
	box2 = new Box(vec3(m_box2pos), vec3(m_box2vel), 3.0f, 1.0f, 1.0f, 1.0f, vec4(0, 1, 0, 1));
	box3 = new Box(vec3(m_box3pos), vec3(m_box3vel), 3.0f, 1.0f, 1.0f, 1.0f, vec4(0, 0, 1, 1));

	ball1 = new Sphere(vec3(m_ball1pos), vec3(m_ball1vel), 3.0f, 1.0f, vec4(1, 1, 0, 1));
	ball2 = new Sphere(vec3(m_ball2pos), vec3(m_ball2vel), 3.0f, 1.0f, vec4(1, 0, 1, 1));
	ball3 = new Sphere(vec3(m_ball3pos), vec3(m_ball3vel), 3.0f, 1.0f, vec4(0, 1, 1, 1));

	//Plane* plane = new Plane(glm::normalize(vec3(1, 0, 0)), 50);

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
	m_physicsScene->addActor(box3);

	m_physicsScene->addActor(ball1);
	m_physicsScene->addActor(ball2);
	m_physicsScene->addActor(ball3);

	//m_physicsScene->addActor(plane);

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
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 41; ++i) \
	{
		Gizmos::addLine(vec3(-20 + i, 0, 20),
						vec3(-20 + i, 0, -20),
						black);
		Gizmos::addLine(vec3(20, 0, -20 + i),
						vec3(-20, 0, -20 + i),
						black);
	}

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));
	
	aie::Input* input = aie::Input::getInstance();

	if (input->wasKeyPressed(aie::INPUT_KEY_R))
	{
		box1->resetPosition(m_box1pos, m_box1vel);
		box2->resetPosition(m_box2pos, m_box2vel);
		box3->resetPosition(m_box3pos, m_box3vel);

		ball1->resetPosition(m_ball1pos, m_ball1vel);
		ball2->resetPosition(m_ball2pos, m_ball2vel);
		ball3->resetPosition(m_ball3pos, m_ball3vel);
	}

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