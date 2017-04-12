#include "Projectile.h"

Projectile::Projectile(GLuint shaderProgram, glm::vec3 position, glm::vec3 velocity, PlayerShip* shooter) {
	vertices = {
		0, 0, 0
	};
	this->position = position;
	this->velocity = velocity;
	this->shooter = shooter;
	lifeTime = 0;
	maxLifeTime = 60;
	Initialize();
	this->shaderProgram = shaderProgram;
	this->color = shooter->color;
	colorID = glGetUniformLocation(shaderProgram, "inColor");
}

void Projectile::Update(double deltaTime) {
	vec3 deltaVelocity = velocity;
	position += deltaVelocity *= deltaTime;
	lifeTime+= deltaTime;
	for (int i = 0; i < PlayerShip::GetNumberOfplayers(); i++)
	{
		if (PlayerShip::GetShip(i) != 0 || PlayerShip::GetShip(i)->health > 0) {
			if (Distance(position, PlayerShip::GetShip(i)->position) < 1 && PlayerShip::GetShip(i) != shooter) {
				PlayerShip::GetShip(i)->Damage();
				Despawn(id);
			}
		}
	}

	if (lifeTime >= maxLifeTime) {
		Despawn(id);
	}

	if (position.x > 250) {
		position.x = 250;
		velocity.x *= -1;
	}
	else if (position.x < -250) {
		position.x = -250;
		velocity.x *= -1;
	}
	if (position.y > 250) {
		position.y = 250;
		velocity.y *= -1;
	}
	else if (position.y < -250) {
		position.y = -250;
		velocity.y *= -1;
	}
}

void Projectile::Render() {
	Actor::Render();
	glPointSize(10);
	glUniform3f(colorID, color.r, color.g, color.b);
	glDrawArrays(GL_POINTS, 0, 1);
}