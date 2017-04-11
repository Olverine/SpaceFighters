#pragma once
#include "Actor.h"
#include <string>
#include <UIText.h>
#include <PlayerShip.h>
class Pickup :
	public Actor
{
	std::string text = "Pickup";
	UIText* label;
	GLuint colorID = 0;
public:
	Pickup(GLuint shaderProgram, std::string text, glm::vec3 color);
	~Pickup();
	void Render();
	void Update(double deltaTime);
	virtual void OnPicked(PlayerShip* player);
};