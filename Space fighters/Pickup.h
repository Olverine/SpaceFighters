#pragma once
#include "Actor.h"
#include <string>
#include <UIText.h>
#include <PlayerShip.h>
class Pickup :
	public Actor
{
	std::string text = "Pickup";
	GLuint colorID = 0;
public:
	UIText label = UIText(NULL, nullptr);
	Pickup(GLuint shaderProgram, std::string text, glm::vec3 color);
	~Pickup();
	void Render();
	void Update(double deltaTime);
	virtual void OnPicked(PlayerShip* player);
};