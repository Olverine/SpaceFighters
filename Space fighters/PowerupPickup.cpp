#include "PowerupPickup.h"
#include "PopText.h"

void PowerupPickup::OnPicked(PlayerShip* ship) {
	ship->powerup = 1;
	ship->UpdateText();
	Spawn(PopText(shaderProgram, GetDefaultFont(), position - vec3(1.5f, 0, 0), vec3(0, 1, 0), "+1"));
	Despawn(label.id);
	Despawn(id);
}