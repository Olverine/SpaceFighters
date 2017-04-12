#pragma once
#include "UIText.h"
#include <Engine.h>
#include <string>
class PopText :
	public UIText
{
public:
	PopText(GLuint shaderProgram, Font* font, glm::vec3 position, glm::vec3 color, std::string text) : UIText(shaderProgram, font) {
		this->position = position;
		this->color = color;
		this->fixedOnScreen = false;
		Initialize();
		SetText(text);
	};

	void Update(double deltaTime);
};