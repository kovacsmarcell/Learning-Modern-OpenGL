#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
static void PrintMatrix(std::string name,glm::mat4 transform)
{
	std::cout << name << " Matrix: " << std::endl;
	std::cout << transform[0][0] << "    " << transform[1][0] << "    " << transform[2][0] << "    " << transform[3][0] << std::endl;
	std::cout << transform[0][1] << "    " << transform[1][1] << "    " << transform[2][1] << "    " << transform[3][1] << std::endl;
	std::cout << transform[0][2] << "    " << transform[1][2] << "    " << transform[2][2] << "    " << transform[3][2] << std::endl;
	std::cout << transform[0][3] << "    " << transform[1][3] << "    " << transform[2][3] << "    " << transform[3][3] << std::endl;
}

struct Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->m_pos = pos;
		this->m_rot = rot;
		this->m_scale = scale;
	}

	~Transform(){}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMatrix = glm::translate(m_pos);
		glm::mat4 scaleMatrix = glm::scale(m_scale);
		glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0.0, 0.0, 1.0));

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline glm::vec3& GetPos() { return m_pos; }
	inline glm::vec3& GetRot() { return m_rot; }
	inline glm::vec3& GetScale() { return m_scale; }

	inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
	inline void SetRot(const glm::vec3& rot) { m_rot = rot; }
	inline void SetScale(const glm::vec3& scale) { m_scale = scale; }

private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};

#endif