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

	float fireRate = 2;
	float fireTime = 0;
public:
	glm::vec3 velocity;
	glm::vec3 color;
	//ParticleEmitter* engineParticles;
	int health = 3;
	UIText healthText = UIText(NULL, nullptr);

	int powerup = 0;
	double powerupTime = 0;

	PlayerShip(int controllerId, GLuint shaderProgram, glm::vec3 color);

	void Update(double deltaTime);
	void Shoot(float);
	void Render();
	void Damage();
	void UpdateText();
	static PlayerShip* GetShip(int playerController);
	static int GetNumberOfplayers();
};