#pragma once
#include "Camera.h"
class MultiChaseCam :
	public Camera
{
public:
	MultiChaseCam() : Camera(vec3(0, 0, 0)) {};
	std::vector<Actor*> targets;
	void Update();
	void RemoveTarget(Actor* target);
};