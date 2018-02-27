#pragma once

#include "Application.h"
#include "PhysicsScene.h"
#include "Sphere.h"
#include <glm/mat4x4.hpp>

class Box;

class PhysicsEngine3DApp : public aie::Application {
public:

	PhysicsEngine3DApp();
	virtual ~PhysicsEngine3DApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	// camera transforms
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	PhysicsScene* m_physicsScene;

	Box* box1;
	Box* box2;
	Box* box3;

	Sphere* ball1;
	Sphere* ball2;
	Sphere* ball3;

	glm::vec3 m_box1pos;
	glm::vec3 m_box2pos;
	glm::vec3 m_box3pos;

	glm::vec3 m_ball1pos;
	glm::vec3 m_ball2pos;
	glm::vec3 m_ball3pos;

	glm::vec3 m_box1vel;
	glm::vec3 m_box2vel;
	glm::vec3 m_box3vel;

	glm::vec3 m_ball1vel;
	glm::vec3 m_ball2vel;
	glm::vec3 m_ball3vel;
};