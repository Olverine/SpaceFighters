#pragma once
#include "Actor.h"
class PowerupSpawner :
	public Actor
{
	GLuint shader = 0;
public:
	double timer = 0;
	int time = 20;
	PowerupSpawner(GLuint shader);
	void Update(double deltaTime);
};

