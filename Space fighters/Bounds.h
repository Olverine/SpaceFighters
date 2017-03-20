#pragma once
#include "Actor.h"
class Bounds :
	public Actor
{
	GLuint colorID;
	glm::vec3 color;
public:
	Bounds(glm::vec2 size, GLuint shaderProgram, glm::vec3 color);

	void Render();
};

