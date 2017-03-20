#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(GLuint shaderProgram)
{
	this->shaderProgram = shaderProgram;
}

void ParticleEmitter::Emit(glm::vec3 position, glm::vec3 velocity) {
	particles.push_back(position);
	velocities.push_back(velocity);
	numberOfParticles++;
}

void ParticleEmitter::Update() {
	Emit(vec3(0,0,0), vec3(0,1,0));
	for (int i = 0; i < numberOfParticles; i++) {
		particles[i] += velocities[i];
		velocities[i] = LerpVector(velocities[i], vec3(0), 0.05f);
	}
	vertices.clear();
	for each (vec3 particle in particles) {
		vertices.push_back(particle.x);
		vertices.push_back(particle.y);
		vertices.push_back(particle.z);
	}
	RebindVertices();
}

void ParticleEmitter::Render() {
	Actor::Render();
	glUniform3f(glGetUniformLocation(shaderProgram, "inColor"), 1, 0, 0);
	glPointSize(10);
	glDrawArrays(GL_POINTS, 0, numberOfParticles);
	glDisableVertexAttribArray(0);
}