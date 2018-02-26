#include "Sphere.h"
#include <Gizmos.h>

Sphere::Sphere(glm::vec3 position, glm::vec3 velocity,
			   float mass, float radius, glm::vec4 colour) :
			   RigidBody(ShapeType::SPHERE, position, velocity, mass)
{
	m_radius = radius;
	m_colour = colour;

	m_moment = 0.5f * mass * radius * radius;
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	//glm::vec3 end = glm::vec3(cos(m_rotation), sin(m_rotation), tan(m_rotation)) * m_radius;

	aie::Gizmos::addSphere(m_position, m_radius, 12, 12, m_colour);
	//aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1, 0, 0, 1));
}
