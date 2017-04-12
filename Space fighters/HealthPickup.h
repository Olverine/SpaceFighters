#pragma once
#include "Pickup.h"
class HealthPickup :
	public Pickup
{
public:
	HealthPickup(GLuint shaderProgram) : Pickup(shaderProgram, "+1", glm::vec3(0, 0.5f, 0)) {}

	void OnPicked(PlayerShip* ship);
};