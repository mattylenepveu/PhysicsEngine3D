#include "Box.h"
#include <Gizmos.h>

Box::Box(glm::vec3 position, glm::vec3 velocity, float mass,
	float width, float height, float depth, glm::vec4 colour) :
	RigidBody(ShapeType::BOX, position, velocity, mass)
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

void Box::fixedUpdate(glm::vec3 gravity, float timeStep)
{
	RigidBody::fixedUpdate(gravity, timeStep);

	//store the local axes
	//float cs = cosf(m_rotation);
	//float sn = sinf(m_rotation);

	/*m_rotXlocX = glm::normalize(glm::vec3(1, 0, 0));
	m_rotXlocY = glm::normalize(glm::vec3(0, cs, -sn));
	m_rotXlocZ = glm::normalize(glm::vec3(0, sn, cs));

	m_rotYlocX = glm::normalize(glm::vec3(cs, 0, -sn));
	m_rotYlocY = glm::normalize(glm::vec3(0, 1, 0));
	m_rotYlocZ = glm::normalize(glm::vec3(sn, 0, cs));

	m_rotZlocX = glm::normalize(glm::vec3(cs, -sn, 0));
	m_rotZlocY = glm::normalize(glm::vec3(sn, cs, 0));
	m_rotZlocZ = glm::normalize(glm::vec3(0, 0, 1));*/
}

void Box::makeGizmo()
{
	aie::Gizmos::addAABBFilled(m_position, m_dimensions, m_colour);
}
