#include "Plane.h"
#include "PhysicsObject.h"
#include "Gizmos.h"
#include <glm\ext.hpp>

Plane::Plane(glm::vec3 normal, float distance) : PhysicsObject(ShapeType::PLANE)
{
	m_distanceToOrigin = distance;
	m_normal = normal;
}

Plane::~Plane()
{
}

void Plane::makeGizmo()
{
	float lineSegmentLength = 300;
	glm::vec3 parallel(m_normal.y, -m_normal.x, m_normal.z);

	glm::vec3 m_centrePoint = m_normal * m_distanceToOrigin;
	glm::vec4 colour(1, 1, 1, 1);
	glm::vec3 start = m_centrePoint + (parallel * lineSegmentLength);
	glm::vec3 end = m_centrePoint - (parallel * lineSegmentLength);

	aie::Gizmos::add2DLine(start, end, colour);
}

void Plane::resolveCollision(RigidBody* actor2)
{
	glm::vec3 normal = m_normal;
	glm::vec3 relativeVelocity = actor2->getVelocity();

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal)
		/ glm::dot(normal, normal * (1 / actor2->getMass()));

	glm::vec3 force = normal * j;

	actor2->applyForce(force);
}
