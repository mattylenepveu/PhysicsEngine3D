#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Plane.h"
#include "Sphere.h"
#include "Box.h"
#include <algorithm>
#include <iostream>
#include <list>

// function pointer array for doing our collisions 
typedef bool(*funcptr)(PhysicsObject*, PhysicsObject*);

static funcptr collisionFunctionArray[] =
{
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere, PhysicsScene::plane2aabb,
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere, PhysicsScene::sphere2aabb,
	PhysicsScene::aabb2Plane, PhysicsScene::aabb2Sphere, PhysicsScene::aabb2aabb,
};

PhysicsScene::PhysicsScene()
{
	m_timeStep = 0.01f;
	m_gravity = glm::vec3(0, 0, 0);
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActors : m_actors)
	{
		delete pActors;
	}
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	remove(std::begin(m_actors), std::end(m_actors), actor);
}

void PhysicsScene::update(float dt)
{
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;

		checkForCollision();
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{
	for (auto pActor : m_actors)
	{
		pActor->debug();
	}
}

bool PhysicsScene::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Collision for this is complex, will attempt later
	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return (sphere2Plane(obj2, obj1));
}

bool PhysicsScene::plane2aabb(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Plane* plane = dynamic_cast<Plane*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	if (plane != nullptr || box != nullptr)
	{
		glm::vec3 v = plane->getNormal();
		glm::vec3 bottomLeft = box->getMin();
		glm::vec3 bottomRight = box->getMin() + glm::vec3(box->getWidth(), 0, 0);
		glm::vec3 topLeft = box->getMin() + glm::vec3(0, box->getHeight(), 0);
		glm::vec3 topRight = box->getMax();

		if (glm::dot(v, bottomLeft) - plane->getDistance() < 0 ||
			glm::dot(v, bottomRight) - plane->getDistance() < 0 ||
			glm::dot(v, topLeft) - plane->getDistance() < 0 ||
			glm::dot(v, topRight) - plane->getDistance() < 0)
		{
			plane->resolveCollision(box);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec3 collisionNormal = plane->getNormal();

		float sphereToPlane = glm::dot(sphere->getPosition(),
			plane->getNormal()) - plane->getDistance();

		if (sphereToPlane < 0)
		{
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = sphere->getRadius() - sphereToPlane;

		if (intersection > 0)
		{
			plane->resolveCollision(sphere);
			return true;
		}
	}

	return false;
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		glm::vec3 v = sphere1->getPosition() - sphere2->getPosition();
		float radiusTotal = sphere1->getRadius() + sphere2->getRadius();

		if (glm::length(v) <= radiusTotal)
		{
			sphere1->resolveCollision(sphere2);

			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2aabb(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	if (sphere != nullptr && box != nullptr)
	{
		glm::vec3 a = glm::clamp(sphere->getPosition(), box->getMin(), box->getMax());
		glm::vec3 v = a - sphere->getPosition();

		if (glm::length(v) <= sphere->getRadius())
		{
			sphere->resolveCollision(box);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::aabb2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return (plane2aabb(obj2, obj1));
}

bool PhysicsScene::aabb2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return (sphere2aabb(obj2, obj1));
}

bool PhysicsScene::aabb2aabb(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);

	if (box1 != nullptr && box2 != nullptr)
	{
		glm::vec3 min1 = box1->getMin();
		glm::vec3 max1 = box1->getMax();

		glm::vec3 min2 = box2->getMin();
		glm::vec3 max2 = box2->getMax();

		if (min1.x <= max2.x &&
			min1.y <= max2.y &&
			max1.x >= min2.x &&
			min1.z <= max2.z &&
			max1.y >= min2.y &&
			max1.z >= min2.z)
		{
			box1->resolveCollision(box2);
			return true;
		}
	}
	return false;
}

void PhysicsScene::checkForCollision()
{
	auto actorCount = m_actors.size();

	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeId1 = object1->getShapeID();
			int shapeId2 = object2->getShapeID();

			// using function pointers
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			funcptr collisionFunctionPtr = collisionFunctionArray[functionIdx];

			// checks if collision occured
			if (collisionFunctionPtr != nullptr)
			{
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}
