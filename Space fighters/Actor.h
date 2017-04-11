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
	GLenum usage = GL_STATIC_DRAW;
	int vertSize = 3;
public:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::vec3 color = glm::vec3(1.0f);

	bool fixedOnScreen = false;

	GLuint shaderProgram;

	Actor();
	virtual void Initialize();
	virtual void RebindVertices();
	virtual void Update(double deltaTime);
	virtual void Render();
};