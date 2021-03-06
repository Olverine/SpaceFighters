#include "HealthPickup.h"
#include "PopText.h"

void HealthPickup::OnPicked(PlayerShip* ship) {
	ship->health++;
	ship->UpdateText();
	new PopText(shaderProgram, GetDefaultFont(), position - vec3(1.5f, 0, 0), vec3(0, 1, 0), "+1");
	Despawn(label);
	Despawn(this);
}