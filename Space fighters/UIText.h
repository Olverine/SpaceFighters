#pragma once
#include <Actor.h>
#include <UIText.h>
#include <Font.h>
class UIText :
	public Actor
{
	int numberOfVerts = 0;
	Font* font;
	GLuint colorID;
public:
	UIText(GLuint shdr, Font* fnt) : Actor() {
		font = fnt;
		shaderProgram = shdr;
		colorID = glGetUniformLocation(shaderProgram, "inColor");


		usage = GL_DYNAMIC_DRAW;
		vertSize = 2;
		fixedOnScreen = true;
	}

	void SetText(std::string text);
	void Render();
};