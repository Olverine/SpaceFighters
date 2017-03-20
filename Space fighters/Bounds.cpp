#include "Bounds.h"



Bounds::Bounds(glm::vec2 size, GLuint shaderProgram, glm::vec3 color)
{
	for (int i = -40; i < 80; i+= 5) {
		vertices.push_back(-size.x / 2);
		vertices.push_back(-size.y / 2);
		vertices.push_back(i);

		vertices.push_back(size.x / 2);
		vertices.push_back(-size.y / 2);
		vertices.push_back(i);

		vertices.push_back(size.x / 2);
		vertices.push_back(-size.y / 2);
		vertices.push_back(i);

		vertices.push_back(size.x / 2);
		vertices.push_back(size.y / 2);
		vertices.push_back(i);

		vertices.push_back(size.x / 2);
		vertices.push_back(size.y / 2);
		vertices.push_back(i);

		vertices.push_back(-size.x / 2);
		vertices.push_back(size.y / 2);
		vertices.push_back(i);

		vertices.push_back(-size.x / 2);
		vertices.push_back(size.y / 2);
		vertices.push_back(i);

		vertices.push_back(-size.x / 2);
		vertices.push_back(-size.y / 2);
		vertices.push_back(i);
	}

	this->shaderProgram = shaderProgram;
	colorID = glGetUniformLocation(shaderProgram, "inColor");
	this->color = color;

	Initialize();
}

void Bounds::Render() {
	Actor::Render();
	glUniform3f(colorID, color.r, color.g, color.b);
	glDrawArrays(GL_LINES, 0, 8 * 40);
}