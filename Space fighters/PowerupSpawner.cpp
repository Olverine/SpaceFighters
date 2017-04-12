#include "PowerupSpawner.h"
#include "PowerupPickup.h"
#include "HealthPickup.h"


PowerupSpawner::PowerupSpawner(GLuint shader)
{
	this->shader = shader;
}

void PowerupSpawner::Update(double deltaTime) {
	timer += deltaTime / 100;

	if (timer >= time) {
		Spawn(new PowerupPickup(shader));
		Spawn(new HealthPickup(shader));
		timer = 0;
	}
}