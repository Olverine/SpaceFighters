#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <GL\glew.h>
class Actor
{
protected:
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	std::vector<GLfloat> vertices;
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	GLuint shaderProgram;

	Actor();
	virtual void Initialize();
	virtual void RebindVertices();
	virtual void Update(double deltaTime);
	virtual void Render();
};