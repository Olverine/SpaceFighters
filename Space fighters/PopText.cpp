#include "PopText.h"

void PopText::Update(double deltaTime) {
	position.y += 0.2f * deltaTime;
	color.r -= 0.02f * deltaTime;
	color.g -= 0.02f * deltaTime;
	color.b -= 0.02f * deltaTime;
}