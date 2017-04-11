#pragma once
#include <Actor.h>
#include <UIText.h>
#include <Font.h>
class UIText :
	public Actor
{
	int numberOfVerts = 0;
	Font* font;
public:
	UIText(GLuint shaderProgram, Font* font);
	void SetText(std::string text);
	void Render();
};