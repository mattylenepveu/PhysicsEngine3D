#pragma once
#include "RigidBody.h"

class Box : public RigidBody
{
public:
	Box() = delete;
	Box(glm::vec3 position, glm::vec3 velocity, float mass,
		float width, float height, float depth, glm::vec4 colour);
	~Box();

	void fixedUpdate(glm::vec3 gravity, float timeStep);
	virtual void makeGizmo();

	float getWidth() { return m_width; }
	float getHeight() { return m_height; }
	float getDepth() { return m_depth; }

	glm::vec3 getDimensions() { return m_dimensions; }
	glm::vec3 getMin() 
	{
		return glm::vec3(m_position.x - m_width,
		m_position.y - m_height, m_position.z - m_depth);
	}
	glm::vec3 getMax() 
	{
		return glm::vec3(m_position.x + m_width,
		m_position.y + m_height, m_position.z + m_depth);
	}

	glm::vec4 getColour() { return m_colour; }

protected:
	float m_width;
	float m_height;
	float m_depth;

	glm::vec3 m_dimensions;
	/*glm::vec3 m_rotXlocX;
	glm::vec3 m_rotXlocY;
	glm::vec3 m_rotXlocZ;
	glm::vec3 m_rotYlocX;
	glm::vec3 m_rotYlocY;
	glm::vec3 m_rotYlocZ;
	glm::vec3 m_rotZlocX;
	glm::vec3 m_rotZlocY;
	glm::vec3 m_rotZlocZ;*/
	glm::vec3 m_min;
	glm::vec3 m_max;

	glm::vec4 m_colour;
};

