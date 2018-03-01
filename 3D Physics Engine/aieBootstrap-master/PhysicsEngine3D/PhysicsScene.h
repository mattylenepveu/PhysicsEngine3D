#pragma once

// Include(s)
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <algorithm>
#include <vector>

// Forward Declare(s)
class PhysicsObject;

class PhysicsScene
{
public:
	//--------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------
	PhysicsScene();

	//--------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------
	~PhysicsScene();

	//--------------------------------------------------------------------------------
	// Adds an actor to actor array allow an object to have proper physics.
	//
	// Param:
	//		actor: A PhysicsObject pointer that adds the actor to the scene
	//--------------------------------------------------------------------------------
	void addActor(PhysicsObject* actor);

	//--------------------------------------------------------------------------------
	// Removes an actor from actor array the Physics Scene.
	//
	// Param:
	//		actor: A PhysicsObject pointer that removes the actor to the scene.
	//--------------------------------------------------------------------------------
	void removeActor(PhysicsObject* actor);

	//--------------------------------------------------------------------------------
	// Updates the class every frame.
	//
	// Param:
	//		dt: A float that can be used as time in equations.
	//--------------------------------------------------------------------------------
	void update(float dt);

	//--------------------------------------------------------------------------------
	// Updates each actor's Gizmos every frame.
	//--------------------------------------------------------------------------------
	void updateGizmos();

	//--------------------------------------------------------------------------------
	// Function used purely for debugging purposes.
	//--------------------------------------------------------------------------------
	void debugScene();

	//--------------------------------------------------------------------------------
	// Allows gravity to be set for the Physics Engine.
	//
	// Param:
	//		gravity: A Vector3 used to set the gravity variable in the engine.
	//--------------------------------------------------------------------------------
	void setGravity(const glm::vec3 gravity) { m_gravity = gravity; }

	//--------------------------------------------------------------------------------
	// Acts a getter for if a class needs access to gravity.
	//
	// Return:
	//		Returns the gravity as a Vector3.
	//--------------------------------------------------------------------------------
	glm::vec3 getGravity() const { return m_gravity; }

	//--------------------------------------------------------------------------------
	// Allows time step to be set for the Physics Engine.
	//
	// Param:
	//		timeStep: A float used to set the time step variable in the engine.
	//--------------------------------------------------------------------------------
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }

	//--------------------------------------------------------------------------------
	// Acts a getter for if a class needs access to the time step.
	//
	// Return:
	//		Returns the time step as a float.
	//--------------------------------------------------------------------------------
	float getTimeStep() const { return m_timeStep; }

	//--------------------------------------------------------------------------------
	// Checks for collision between two planes.
	//
	// Param:
	//		obj1: A PhysicsObject pointer used for collision math.
	//		obj2: Another PhysicsObject pointer used for collision math.
	// Return:
	//		Returns if the collision has occured.
	//--------------------------------------------------------------------------------
	static bool plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------
	// Checks for collision between a plane and a sphere.
	//
	// Param:
	//		obj1: A PhysicsObject pointer used for collision math.
	//		obj2: Another PhysicsObject pointer used for collision math.
	// Return:
	//		Returns if the collision has occured.
	//--------------------------------------------------------------------------------
	static bool plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------
	// Checks for collision between a plane and a box.
	//
	// Param:
	//		obj1: A PhysicsObject pointer used for collision math.
	//		obj2: Another PhysicsObject pointer used for collision math.
	// Return:
	//		Returns if the collision has occured.
	//--------------------------------------------------------------------------------
	static bool plane2aabb(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------
	// Checks for collision between a sphere and a plane.
	//
	// Param:
	//		obj1: A PhysicsObject pointer used for collision math.
	//		obj2: Another PhysicsObject pointer used for collision math.
	// Return:
	//		Returns if the collision has occured.
	//--------------------------------------------------------------------------------
	static bool sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------
	// Checks for collision between two spheres.
	//
	// Param:
	//		obj1: A PhysicsObject pointer used for collision math.
	//		obj2: Another PhysicsObject pointer used for collision math.
	// Return:
	//		Returns if the collision has occured.
	//--------------------------------------------------------------------------------
	static bool sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------
	// Checks for collision between a sphere and a box.
	//
	// Param:
	//		obj1: A PhysicsObject pointer used for collision math.
	//		obj2: Another PhysicsObject pointer used for collision math.
	// Return:
	//		Returns if the collision has occured.
	//--------------------------------------------------------------------------------
	static bool sphere2aabb(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------
	// Checks for collision between a box and a plane.
	//
	// Param:
	//		obj1: A PhysicsObject pointer used for collision math.
	//		obj2: Another PhysicsObject pointer used for collision math.
	// Return:
	//		Returns if the collision has occured.
	//--------------------------------------------------------------------------------
	static bool aabb2Plane(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------
	// Checks for collision between a box and a sphere.
	//
	// Param:
	//		obj1: A PhysicsObject pointer used for collision math.
	//		obj2: Another PhysicsObject pointer used for collision math.
	// Return:
	//		Returns if the collision has occured.
	//--------------------------------------------------------------------------------
	static bool aabb2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------
	// Checks for collision between two boxes.
	//
	// Param:
	//		obj1: A PhysicsObject pointer used for collision math.
	//		obj2: Another PhysicsObject pointer used for collision math.
	// Return:
	//		Returns if the collision has occured.
	//--------------------------------------------------------------------------------
	static bool aabb2aabb(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------
	// Function checks to see if any collision has occured.
	//--------------------------------------------------------------------------------
	void checkForCollision();

protected:
	// Used to indicate an array of PhysicsObjects as actors
	std::vector<PhysicsObject*> m_actors;

	// Vector3 used as a variable for gravity
	glm::vec3 m_gravity;

	// Float used as a variable for time step
	float m_timeStep;
};
