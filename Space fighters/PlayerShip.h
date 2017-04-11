#pragma once
#include <ParticleEmitter.h>
#include <Projectile.h>
#include <UIText.h>

class PlayerShip : public Actor
{
	// Between 0 and 1!
	float angularSpeed = 0.2f;
	float acceleration = 0.25f;
	float drag = 0.005f;
	int playerControllerId; 
	GLuint colorID;
public:
	glm::vec3 velocity;
	glm::vec3 color;
	//ParticleEmitter* engineParticles;
	int health = 3;
	UIText *healthText;

	PlayerShip(int controllerId, GLuint shaderProgram, glm::vec3 color);

	void Update(double deltaTime);
	void Render();
	void Damage();
	static PlayerShip* GetShip(int playerController);
	static int GetNumberOfplayers();
};