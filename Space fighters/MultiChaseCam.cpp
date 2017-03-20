#include "MultiChaseCam.h"

void MultiChaseCam::Update() {
	position = vec3(0);

	float minX = -500;
	float minY = -500;
	float maxX = 500;
	float maxY = 500;

	for each (Actor* actor in targets)
	{
		position += actor->position;
		if (actor->position.x < minX) {
			minX = actor->position.x;
		}
		else if (actor->position.x > maxX) {
			maxX = actor->position.x;
		}

		if (actor->position.y < minY) {
			minY = actor->position.y;
		}
		else if (actor->position.y > maxY) {
			maxY = actor->position.y;
		}
	}

	position /= targets.size();
	lookAt = position;
	position += vec3(0, 0, 64);
}

void MultiChaseCam::RemoveTarget(Actor* target) {
	for (int i = 0; i < targets.size(); i++) {
		if (targets[i] == target) {
			targets.erase(targets.begin() + i);
		}
	}
}