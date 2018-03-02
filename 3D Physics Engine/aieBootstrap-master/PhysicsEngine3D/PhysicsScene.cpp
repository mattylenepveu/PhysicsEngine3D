// Include(s)
#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Plane.h"
#include "Sphere.h"
#include "Box.h"
#include <algorithm>
#include <iostream>
#include <list>

// Function pointer array for doing our collisions 
typedef bool(*funcptr)(PhysicsObject*, PhysicsObject*);

//--------------------------------------------------------------------------------
// Array used to store collision functions so they can be accessed elsewhere.
//--------------------------------------------------------------------------------
static funcptr collisionFunctionArray[] =
{
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere, PhysicsScene::plane2aabb,
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere, PhysicsScene::sphere2aabb,
	PhysicsScene::aabb2Plane, PhysicsScene::aabb2Sphere, PhysicsScene::aabb2aabb,
};

//--------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------
PhysicsScene::PhysicsScene()
{
	// Sets default values for time step and gravity
	m_timeStep = 0.01f;
	m_gravity = glm::vec3(0, 0, 0);
}

//--------------------------------------------------------------------------------
// Default Destructor.
//--------------------------------------------------------------------------------
PhysicsScene::~PhysicsScene()
{
	// Goes through and deletes all actors in the array
	for (auto pActors : m_actors)
	{
		delete pActors;
	}
}

//--------------------------------------------------------------------------------
// Adds an actor to actor array allow an object to have proper physics.
//
// Param:
//		actor: A PhysicsObject pointer that adds the actor to the scene
//--------------------------------------------------------------------------------
void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

//--------------------------------------------------------------------------------
// Removes an actor from actor array the Physics Scene.
//
// Param:
//		actor: A PhysicsObject pointer that removes the actor to the scene.
//--------------------------------------------------------------------------------
void PhysicsScene::removeActor(PhysicsObject* actor)
{
	remove(std::begin(m_actors), std::end(m_actors), actor);
}

//--------------------------------------------------------------------------------
// Updates the class every frame.
//
// Param:
//		dt: A float that can be used as time in equations.
//--------------------------------------------------------------------------------
void PhysicsScene::update(float dt)
{
	// Initilizes a time variable and sets it to zero by default
	static float accumulatedTime = 0.0f;

	// Runs it via delta time
	accumulatedTime += dt;

	// Code in braces while timer is greater than or equal to time step
	while (accumulatedTime >= m_timeStep)
	{
		// Calls each actor's update function, passing in gravity and timestep 
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		// Minuses accumulated time by the time step
		accumulatedTime -= m_timeStep;

		// Checks for any collision in the engine
		checkForCollision();
	}
}

//--------------------------------------------------------------------------------
// Updates each actor's Gizmos every frame.
//--------------------------------------------------------------------------------
void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}

//--------------------------------------------------------------------------------
// Function used purely for debugging purposes.
//--------------------------------------------------------------------------------
void PhysicsScene::debugScene()
{
	for (auto pActor : m_actors)
	{
		pActor->debug();
	}
}

//--------------------------------------------------------------------------------
// Checks for collision between two planes.
//
// Param:
//		obj1: A PhysicsObject pointer used for collision math.
//		obj2: Another PhysicsObject pointer used for collision math.
// Return:
//		Returns if the collision has occured.
//--------------------------------------------------------------------------------
bool PhysicsScene::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Collision for this is complex so I did not attempt
	return false;
}

//--------------------------------------------------------------------------------
// Checks for collision between a plane and a sphere.
//
// Param:
//		obj1: A PhysicsObject pointer used for collision math.
//		obj2: Another PhysicsObject pointer used for collision math.
// Return:
//		Returns if the collision has occured.
//--------------------------------------------------------------------------------
bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Calls sphere2plane and passes in opposite parameters
	return (sphere2Plane(obj2, obj1));
}

//--------------------------------------------------------------------------------
// Checks for collision between a plane and a box.
//
// Param:
//		obj1: A PhysicsObject pointer used for collision math.
//		obj2: Another PhysicsObject pointer used for collision math.
// Return:
//		Returns if the collision has occured.
//--------------------------------------------------------------------------------
bool PhysicsScene::plane2aabb(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Dynamically casts a plane and box as the passed in objects
	Plane* plane = dynamic_cast<Plane*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	// Checks to see if plane and box are casted
	if (plane != nullptr || box != nullptr)
	{
		// Gets the plane's normal and stores it in a local Vector3
		glm::vec3 v = plane->getNormal();

		// Gets the minimum of the box and stores it as the bottom left corner
		glm::vec3 bottomLeftBelow = box->getMin();

		// Calculates the bottom right corner of the box
		glm::vec3 bottomRightBelow = box->getMin() + glm::vec3(box->getWidth(), 0, 0);

		// Calculates the top left corner of the box
		glm::vec3 topLeftBelow = box->getMin() + glm::vec3(0, box->getHeight(), 0);

		// Gets the maximum of the box and stores it as the top right corner
		glm::vec3 topRightBelow = box->getMax();

		// Gets the minimum of the box and stores it as the bottom left corner
		glm::vec3 bottomLeftAbove = box->getMin() + glm::vec3(0, 0, box->getDepth());

		// Calculates the bottom right corner of the box
		glm::vec3 bottomRightAbove = box->getMin() + glm::vec3(box->getWidth(), 0, box->getDepth());

		// Calculates the top left corner of the box
		glm::vec3 topLeftAbove = box->getMin() + glm::vec3(0, box->getHeight(), box->getDepth());

		// Gets the maximum of the box and stores it as the top right corner
		glm::vec3 topRightAbove = box->getMax() + glm::vec3(0, 0, box->getDepth());
		
		float ol[8] = { 0.0f };

		ol[0] = glm::dot(v, bottomLeftBelow) - plane->getDistance();
		ol[1] = glm::dot(v, bottomRightBelow) - plane->getDistance();
		ol[2] = glm::dot(v, topLeftBelow) - plane->getDistance();
		ol[3] = glm::dot(v, topRightBelow) - plane->getDistance();
		ol[4] = glm::dot(v, bottomLeftBelow) - plane->getDistance();
		ol[5] = glm::dot(v, bottomRightBelow) - plane->getDistance();
		ol[6] = glm::dot(v, topLeftBelow) - plane->getDistance();
		ol[7] = glm::dot(v, topRightBelow) - plane->getDistance();

		float maxOl = 0;

		for (int i = 0; i < 8; ++i)
		{
			if (ol[i] < maxOl)
			{
				maxOl = ol[i];
			}
		}
		
		if (maxOl < 0)
		{
			// Calculates the contact between the box and plane
			glm::vec3 contact = box->getPosition() + (v * -box->getWidth());

			// Calls plane's resolveCollision function passing in the box and contact
			plane->resolveCollision(box);

			box->setPosition(box->getPosition() - plane->getNormal() * maxOl);

			// Returns true as collision has been detected
			return true;
		}
	}

	// Returns false if there has been no collision
	return false;
}

//--------------------------------------------------------------------------------
// Checks for collision between a sphere and a plane.
//
// Param:
//		obj1: A PhysicsObject pointer used for collision math.
//		obj2: Another PhysicsObject pointer used for collision math.
// Return:
//		Returns if the collision has occured.
//--------------------------------------------------------------------------------
bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Dynamically casts the sphere and plane as the passed in objects
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	// Checks if the sphere and plane have been casted
	if (sphere != nullptr && plane != nullptr)
	{
		// Gets the plane's normal and stores it in local Vector3
		glm::vec3 collisionNormal = plane->getNormal();

		// Calculates the dot product of the sphere and plane
		float sphereToPlane = glm::dot(sphere->getPosition(),
									   plane->getNormal()) - plane->getDistance();

		// Checks if the dot product is less than zero
		if (sphereToPlane < 0)
		{
			// Makes the normal and the dot product negative values
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		// Calculates the sphere's radius minus the dot product
		float intersection = sphere->getRadius() - sphereToPlane;

		// Checks if the intersection variable is greater than zero
		if (intersection > 0)
		{
			// Calculates the contact between the sphere and plane
			glm::vec3 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());

			// Calls plane's resolve collision function passing in the sphere
			plane->resolveCollision(sphere/*, contact*/);

			// Sets position of the sphere back so it doesn't fall through the plane
			sphere->setPosition(contact + collisionNormal * 
							   (sphere->getRadius() + intersection));


			// Returns true as there is collision detected
			return true;
		}
	}

	// Returns false if there is no collision detected
	return false;
}

//--------------------------------------------------------------------------------
// Checks for collision between two spheres.
//
// Param:
//		obj1: A PhysicsObject pointer used for collision math.
//		obj2: Another PhysicsObject pointer used for collision math.
// Return:
//		Returns if the collision has occured.
//--------------------------------------------------------------------------------
bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Dynamically casts the two spheres as the passed in objects
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		// Finds the difference between the two sphere's location
		glm::vec3 v = sphere1->getPosition() - sphere2->getPosition();

		// Gets the length of that distance vector
		float distance = glm::length(v);

		// Calculates to see if there is any intersection with the two spheres
		float intersection = sphere1->getRadius() + sphere2->getRadius() - distance;

		// Checks if the intersection variable is greater than zero
		if (intersection > 0)
		{
			// Calculates the correct contact force in which to apply to both spheres
			glm::vec3 contactForce = 0.5f * (distance - (sphere1->getRadius() + 
											 sphere2->getRadius())) * v / distance;

			// Sets the position of both spheres back to make them not collide
			sphere1->setPosition(sphere1->getPosition() + contactForce);
			sphere2->setPosition(sphere2->getPosition() - contactForce);

			// Calls one sphere's resolveCollision function
			sphere1->resolveCollision(sphere2/*, 0.05f * (sphere1->getPosition() + 
													   sphere2->getPosition())*/);

			// Returns true as there is collision detected
			return true;
		}
	}

	// Returns false if there is no collision detected
	return false;
}

//--------------------------------------------------------------------------------
// Checks for collision between a sphere and a box.
//
// Param:
//		obj1: A PhysicsObject pointer used for collision math.
//		obj2: Another PhysicsObject pointer used for collision math.
// Return:
//		Returns if the collision has occured.
//--------------------------------------------------------------------------------
bool PhysicsScene::sphere2aabb(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Dynamically casts the sphere and the plane as the passed in objects
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	// Checks if the sphere and the box have been casted
	if (sphere != nullptr && box != nullptr)
	{
		// Clamps the spheres position and the boxes' min and max
		glm::vec3 a = glm::clamp(sphere->getPosition(), box->getMin(), box->getMax());

		// Finds the difference between the clamped vector and the sphere's position
		glm::vec3 v = a - sphere->getPosition();

		// Checks if the length v is less than or equal to the sphere's radius
		if (glm::length(v) <= sphere->getRadius())
		{
			// Normalizes v and stores it in local variable
			glm::vec3 cn = glm::normalize(v);

			// Calculates the overlap between the sphere and box
			glm::vec3 ol = sphere->getRadius() - v;

			// Calls sphere's resolveCollision function passing in box and collision normal
			sphere->resolveCollision(box/*, cn*/);

			// Returns true as there is collision detected
			return true;
		}
	}

	// Returns false if there is no collision detected
	return false;
}

//--------------------------------------------------------------------------------
// Checks for collision between a box and a plane.
//
// Param:
//		obj1: A PhysicsObject pointer used for collision math.
//		obj2: Another PhysicsObject pointer used for collision math.
// Return:
//		Returns if the collision has occured.
//--------------------------------------------------------------------------------
bool PhysicsScene::aabb2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Calls plane2aabb and passes in opposite parameters
	return (plane2aabb(obj2, obj1));
}

//--------------------------------------------------------------------------------
// Checks for collision between a box and a sphere.
//
// Param:
//		obj1: A PhysicsObject pointer used for collision math.
//		obj2: Another PhysicsObject pointer used for collision math.
// Return:
//		Returns if the collision has occured.
//--------------------------------------------------------------------------------
bool PhysicsScene::aabb2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Calls sphere2aabb and passes in opposite parameters
	return (sphere2aabb(obj2, obj1));
}

//--------------------------------------------------------------------------------
// Checks for collision between two boxes.
//
// Param:
//		obj1: A PhysicsObject pointer used for collision math.
//		obj2: Another PhysicsObject pointer used for collision math.
// Return:
//		Returns if the collision has occured.
//--------------------------------------------------------------------------------
bool PhysicsScene::aabb2aabb(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Dynamically casts the two boxes as the passed in objects
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);

	// Checks to see if the two boxes have been casted
	if (box1 != nullptr && box2 != nullptr)
	{
		// Gets box 1's min and max
		glm::vec3 min1 = box1->getMin();
		glm::vec3 max1 = box1->getMax();

		// Gets box 2's min and max
		glm::vec3 min2 = box2->getMin();
		glm::vec3 max2 = box2->getMax();

		// Calculates and checks to see if any overlap has occured
		if (min1.x <= max2.x &&
			min1.y <= max2.y &&
			max1.x >= min2.x &&
			min1.z <= max2.z &&
			max1.y >= min2.y &&
			max1.z >= min2.z)
		{
			box1->resolveCollision(box2);

			// Returns true as there is collision detected
			return true;
		}
	}

	// Returns false if there is no collision detected
	return false;
}

//--------------------------------------------------------------------------------
// Function checks to see if any collision has occured.
//--------------------------------------------------------------------------------
void PhysicsScene::checkForCollision()
{
	// Gets the size of the actor's array and stores it in local variable
	auto actorCount = m_actors.size();

	// Runs double for loop to check the type of two objects
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			// Assigns two local PhysicsObjects as indexed numbers in actors array
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];

			// Gets and stores the two object's shape ID in local int
			unsigned short int shapeId1 = object1->getShapeID();
			unsigned short int shapeId2 = object2->getShapeID();

			// Calculates the correct index for function pointer
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;

			// Calls an indexed function from the function pointer
			funcptr collisionFunctionPtr = collisionFunctionArray[functionIdx];

			// Checks if collision occured
			if (collisionFunctionPtr != nullptr)
			{
				// Passes in the indexed actors into selected function in function pointer
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}
