#include "Projectile.h"

Projectile::Projectile(glm::vec3 position, glm::vec3 velocity, PlayerShip* shooter) {
	vertices = {
		0, 0, 0
	};
	this->position = position;
	this->velocity = velocity;
	this->shooter = shooter;
	lifeTime = 0;
	maxLifeTime = 60;
	Initialize();
	this->color = shooter->color;
	colorID = glGetUniformLocation(shaderProgram, "inColor");
}

void Projectile::Update(double deltaTime) {
	vec3 deltaVelocity = velocity;
	position += deltaVelocity *= deltaTime;
	lifeTime+= deltaTime;
	for (int i = 0; i < PlayerShip::GetNumberOfplayers(); i++)
	{
		if (Distance(position, PlayerShip::GetShip(i)->position) < 1 && PlayerShip::GetShip(i) != shooter) {
			PlayerShip::GetShip(i)->Damage();
			Despawn(this);
		}
	}

	if (lifeTime >= maxLifeTime) {
		Despawn(this);
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