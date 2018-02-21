#include "Box.h"
#include <Gizmos.h>

Box::Box(glm::vec3 position, glm::vec3 velocity, float mass,
	float width, float height, float depth, glm::vec4 colour) :
	RigidBody(ShapeType::BOX, position, velocity, 0, mass, 0.2f, 0.2f, 0.8f)
{
	m_width = width;
	m_height = height;
	m_depth = depth;

	m_dimensions = glm::vec3(m_width, m_height, m_depth);
	m_moment = 1.0f / 12.0f * mass * width * height;

	m_colour = colour;
}

Box::~Box()
{
}

void Box::makeGizmo()
{
	aie::Gizmos::addAABBFilled(m_position, m_dimensions, m_colour);
}
