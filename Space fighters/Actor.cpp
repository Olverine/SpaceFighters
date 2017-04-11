#include "Actor.h"

Actor::Actor() {
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

void Actor::Initialize() { 
	glGenBuffers(1, &vertexbuffer);
	RebindVertices();
}

void Actor::RebindVertices()
{
	if (vertices.size() > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], usage);
	}
}

void Actor::Update(double deltaTime) {

}

void Actor::Render() {
	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, vertSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
}