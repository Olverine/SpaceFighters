#include "PowerupPickup.h"
#include "PopText.h"

void PowerupPickup::OnPicked(PlayerShip* ship) {
	ship->powerup = rand() % 3 + 1;
	ship->powerupTime = 10;
	ship->UpdateText();
	Spawn(new PopText(shaderProgram, GetDefaultFont(), position - vec3(2.0f, 0, 0), vec3(0, 1, 0), "WOW"));
	Despawn(label);
	Despawn(this);
}