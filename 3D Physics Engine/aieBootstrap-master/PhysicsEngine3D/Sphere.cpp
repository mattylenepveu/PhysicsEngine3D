#include "Sphere.h"
#include <Gizmos.h>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity,
			   float mass, float radius, glm::vec4 colour) :
			   RigidBody(ShapeType::SPHERE, position, velocity, 0, mass, 0.2f, 0.2f, 0)
{
	m_radius = radius;
	m_colour = colour;
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
}
