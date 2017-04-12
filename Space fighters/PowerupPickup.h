#pragma once
#include "Pickup.h"
class PowerupPickup :
	public Pickup
{
public:
	PowerupPickup(GLuint shaderProgram) : Pickup(shaderProgram, "Upgrade", glm::vec3(0, 0.2f, 0.5f)) {}

	void OnPicked(PlayerShip* player);
};