#pragma once
#include <Actor.h>
#include <Engine.h>

class ParticleEmitter : public Actor
{
	std::vector<glm::vec3> particles;
	std::vector<glm::vec3> velocities;
public:
	int numberOfParticles;
	float lifeTime;
	ParticleEmitter(GLuint shaderProgram);

	void Emit(glm::vec3, glm::vec3);
	void Update();
	void Render();
};

