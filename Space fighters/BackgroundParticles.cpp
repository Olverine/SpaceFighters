#include "BackgroundParticles.h"



BackgroundParticles::BackgroundParticles(glm::vec3 area, int particles, GLuint shaderProgram)
{
	for (int i = 0; i < particles; i++) {
		glm::vec3 position = glm::vec3(rand() % (int)area.x, rand() % (int)area.y, rand() % (int)area.z);
		vertices.push_back(position.x - size - (area.x / 2));
		vertices.push_back(position.y + size - (area.y / 2));
		vertices.push_back(position.z - area.z - 1);
		vertices.push_back(position.x + size - (area.x / 2));
		vertices.push_back(position.y + size - (area.y / 2));
		vertices.push_back(position.z - area.z - 1);
		vertices.push_back(position.x + size - (area.x / 2));
		vertices.push_back(position.y - size - (area.y / 2));
		vertices.push_back(position.z - area.z - 1);

		vertices.push_back(position.x - size - (area.x / 2));
		vertices.push_back(position.y + size - (area.y / 2));
		vertices.push_back(position.z - area.z - 1);
		vertices.push_back(position.x - size - (area.x / 2));
		vertices.push_back(position.y - size - (area.y / 2));
		vertices.push_back(position.z - area.z - 1);
		vertices.push_back(position.x + size - (area.x / 2));
		vertices.push_back(position.y - size - (area.y / 2));
		vertices.push_back(position.z - area.z - 1);
	}
	this->shaderProgram = shaderProgram;
	colorID = glGetUniformLocation(shaderProgram, "inColor");
}

void BackgroundParticles::Render() {
	Actor::Render();
	glUniform3f(colorID, 1, 1, 1);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}