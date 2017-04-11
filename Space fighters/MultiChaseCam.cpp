#include "MultiChaseCam.h"

void MultiChaseCam::Update() {
	position = vec3(0);

	float minX = 500;
	float minY = 500;
	float maxX = -500;
	float maxY = -500;

	for each (Actor* actor in targets)
	{
		position += actor->position;
		if (actor->position.x < minX) {
			minX = actor->position.x;
		}
		if (actor->position.x > maxX) {
			maxX = actor->position.x;
		}

		if (actor->position.y < minY) {
			minY = actor->position.y;
		}
		if (actor->position.y > maxY) {
			maxY = actor->position.y;
		}
	}

	float zoom = 0;

	zoom = sqrt(pow(maxX - minX, 2) + pow(maxY - minY, 2));
	zoom *= 1.5f;

	if (zoom < 64) zoom = 64;

	position /= targets.size();
	lookAt = position;
	position += vec3(0, 0, zoom);
}

void MultiChaseCam::RemoveTarget(Actor* target) {
	for (int i = 0; i < targets.size(); i++) {
		if (targets[i] == target) {
			targets.erase(targets.begin() + i);
		}
	}
}