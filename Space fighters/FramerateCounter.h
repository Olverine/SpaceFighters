#pragma once
#include "UIText.h"
#include <Engine.h>
class FramerateCounter :
	public UIText
{
public:
	FramerateCounter(GLuint shaderProgram) : UIText(shaderProgram, GetDefaultFont()) {
	};

	void Update(double deltaTime);
};

