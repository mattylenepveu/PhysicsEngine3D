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
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	PhysicsScene* m_physicsScene;

	/*Box* wall1;
	Box* wall2;
	Box* wall3;
	Box* wall4;
	Box* wall5;*/
};