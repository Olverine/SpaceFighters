#pragma once
#include "Actor.h"
class BackgroundParticles :
	public Actor
{
	GLuint colorID;
	float size = 0.2f;
public:
	BackgroundParticles(glm::vec3 area, int particles, GLuint shaderProgram);

	void Render();
};

