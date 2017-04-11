#pragma once
#include <Engine.h>
#include <PlayerShip.h>

class PlayerShip;

class Projectile : public Actor
{
	double lifeTime;
	int maxLifeTime = 0;
	GLuint colorID;
	PlayerShip* shooter;
public:
	glm::vec3 color;
	glm::vec3 velocity;
	Projectile(GLuint shaderProgram, glm::vec3, glm::vec3, PlayerShip* shooter);

	void Update(double deltaTime);
	void Render();
};